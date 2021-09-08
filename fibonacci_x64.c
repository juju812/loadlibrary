//
// Copyright (C) 2017 Tavis Ormandy
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/unistd.h>
#ifndef __APPLE__
#include <asm/unistd.h>
#endif
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
// #include <mcheck.h>
#include <err.h>

#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"
#include "util.h"
#include "log.h"
#include "hook.h"

struct pe_image image = {
        .entry  = NULL,
        .name   = "TestDll_x64.dll",
};

// export functions
void WINAPI (*fibonacci_init)(const unsigned long long, const unsigned long long);
bool WINAPI (*fibonacci_next)();
unsigned long long WINAPI (*fibonacci_current)();
unsigned WINAPI (*fibonacci_index)();

// Any usage limits to prevent bugs disrupting system.
const struct rlimit kUsageLimits[] = {
    [RLIMIT_FSIZE]  = { .rlim_cur = 0x20000000, .rlim_max = 0x20000000 },
    [RLIMIT_CPU]    = { .rlim_cur = 3600,       .rlim_max = RLIM_INFINITY },
    [RLIMIT_CORE]   = { .rlim_cur = 0,          .rlim_max = 0 },
    [RLIMIT_NOFILE] = { .rlim_cur = 10240,         .rlim_max = 10240 },
};

VOID ResourceExhaustedHandler(int Signal)
{
    errx(EXIT_FAILURE, "Resource Limits Exhausted, Signal %d", Signal);
}

int main(int argc, char **argv, char **envp)
{
    PIMAGE_DOS_HEADER DosHeader;
    PIMAGE_NT_HEADERS PeHeader;

    // Load the mpengine module.
    if (!pe_load_library(image.name, &image.image, &image.size)) {
        LogMessage("You must add the dll and vdm files to the engine directory");
        return 1;
    }

    // Handle relocations, imports, etc.
    link_pe_images(&image, 1);
    // read_exports(&image);

    // Lookup export functions...
    if (get_export("fibonacci_init", &fibonacci_init) == -1) {
        errx(EXIT_FAILURE, "failed to resolve function fibonacci_init");
    }

    if (get_export("fibonacci_next", &fibonacci_next) == -1) {
        errx(EXIT_FAILURE, "failed to resolve function fibonacci_next");
    }

    if (get_export("fibonacci_current", &fibonacci_current) == -1) {
        errx(EXIT_FAILURE, "failed to resolve function fibonacci_current");
    }

    if (get_export("fibonacci_index", &fibonacci_index) == -1) {
        errx(EXIT_FAILURE, "failed to resolve function fibonacci_index");
    }

    setup_nt_threadinfo(NULL);

    // Fetch the headers to get base offsets.
    DosHeader   = (PIMAGE_DOS_HEADER) image.image;
    PeHeader    = (PIMAGE_NT_HEADERS)(image.image + DosHeader->e_lfanew);

    // Load any additional exports.
    if (!process_extra_exports(image.image, PeHeader->OptionalHeader.BaseOfCode, "TestDll.map")) {
#ifndef NDEBUG
        LogMessage("The map file wasn't found, symbols wont be available");
#endif
    } else {
        // Calculate the commands needed to get export and map symbols visible in gdb.
        if (IsGdbPresent()) {
            LogMessage("GDB: add-symbol-file %s %#x+%#x",
                       image.name,
                       image.image,
                       PeHeader->OptionalHeader.BaseOfCode);
            LogMessage("GDB: shell bash genmapsym.sh %#x+%#x symbols_%d.o < %s",
                       image.image,
                       PeHeader->OptionalHeader.BaseOfCode,
                       getpid(),
                       "engine/mpengine.map");
            LogMessage("GDB: add-symbol-file symbols_%d.o 0", getpid());
            __debugbreak();
        }
    }

    // Call DllMain()
    // image.entry((HANDLE) 'FIBONACCI', DLL_PROCESS_ATTACH, NULL);

    // Install usage limits to prevent system crash.
    setrlimit(RLIMIT_CORE, &kUsageLimits[RLIMIT_CORE]);
    setrlimit(RLIMIT_CPU, &kUsageLimits[RLIMIT_CPU]);
    setrlimit(RLIMIT_FSIZE, &kUsageLimits[RLIMIT_FSIZE]);
    setrlimit(RLIMIT_NOFILE, &kUsageLimits[RLIMIT_NOFILE]);

    signal(SIGXCPU, ResourceExhaustedHandler);
    signal(SIGXFSZ, ResourceExhaustedHandler);

// # ifndef NDEBUG
//     // Enable Maximum heap checking.
//     mcheck_pedantic(NULL);
// # endif

    fibonacci_init(1, 1);
    do {
        fprintf(stdout, "%d: %llu\n", fibonacci_index(), fibonacci_current());
    } while (fibonacci_next());
    // Report count of values written before overflow.
    fprintf(stdout, "%d Fibonacci sequence values fit in an unsigned 64-bit integer.\n", fibonacci_index() + 1);

    pe_unload_library(image);
    return 0;
}
