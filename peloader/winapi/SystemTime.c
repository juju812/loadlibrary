#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "winnt_types.h"
#include "log.h"
#include "winexports.h"
#include "util.h"

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME;

extern void WINAPI SetLastError(DWORD dwErrCode);

// These routines are called to check if signing certificates have expired, so
// should return similar values.

STATIC VOID WINAPI GetSystemTime(PSYSTEMTIME lpSystemTime) {
    memset(lpSystemTime, 0, sizeof(SYSTEMTIME));
    return;
}

STATIC BOOL WINAPI SystemTimeToFileTime(SYSTEMTIME *lpSystemTime, PFILETIME lpFileTime) {
    memset(lpFileTime, 0, sizeof(FILETIME));
    return TRUE;
}

STATIC VOID WINAPI GetSystemTimePreciseAsFileTime(PFILETIME lpSystemTimeAsFileTime) {
    memset(lpSystemTimeAsFileTime, 0, sizeof(FILETIME));
    return;
}

STATIC VOID WINAPI GetSystemTimeAsFileTime(PVOID lpSystemTimeAsFileTime) {
    memset(lpSystemTimeAsFileTime, 0, sizeof(FILETIME));
    return;
}

STATIC BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount) {
    struct timespec tm;
    DebugLog("");

    SetLastError(0);
#ifdef __APPLE__
    if (clock_gettime(CLOCK_MONOTONIC, &tm) != 0)
#else
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &tm) != 0)
#endif
        return FALSE;

    *lpPerformanceCount = tm.tv_nsec;

    return TRUE;
}

STATIC DWORD WINAPI GetTickCount(VOID) {
    return 0;
}

STATIC ULONGLONG WINAPI GetTickCount64(VOID) {
    return 0;
}

STATIC BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency) {
    struct timespec tm;

    DebugLog("");

#ifdef __APPLE__
    if (clock_gettime(CLOCK_MONOTONIC, &tm) != 0)
#else
    if (clock_gettime(CLOCK_MONOTONIC_RAW, &tm) != 0)
#endif
        return FALSE;

    *lpFrequency = tm.tv_nsec;

    SetLastError(0);

    return TRUE;
}

STATIC BOOL WINAPI
GetProcessTimes(HANDLE hProcess, PFILETIME lpCreationTime, PFILETIME lpExitTime, PFILETIME lpKernelTime,
                PFILETIME lpUserTime) {
    SetLastError(0);
    DebugLog("");
    return FALSE;
}

STATIC BOOL WINAPI DosDateTimeToFileTime(WORD wFatDate, WORD wFatTime, PFILETIME lpFileTime) {
    DebugLog("");
    return FALSE;
}

STATIC BOOL WINAPI FileTimeToSystemTime(PFILETIME lpFileTime, PSYSTEMTIME lpSystemTime) {
    DebugLog("");
    return FALSE;
}

DECLARE_CRT_EXPORT("GetSystemTime", GetSystemTime);

DECLARE_CRT_EXPORT("SystemTimeToFileTime", SystemTimeToFileTime);

DECLARE_CRT_EXPORT("GetSystemTimePreciseAsFileTime", GetSystemTimePreciseAsFileTime);

DECLARE_CRT_EXPORT("GetSystemTimeAsFileTime", GetSystemTimeAsFileTime);

DECLARE_CRT_EXPORT("QueryPerformanceCounter", QueryPerformanceCounter);

DECLARE_CRT_EXPORT("QueryPerformanceFrequency", QueryPerformanceFrequency);

DECLARE_CRT_EXPORT("GetTickCount", GetTickCount);

DECLARE_CRT_EXPORT("GetTickCount64", GetTickCount64);

DECLARE_CRT_EXPORT("GetProcessTimes", GetProcessTimes);

DECLARE_CRT_EXPORT("DosDateTimeToFileTime", DosDateTimeToFileTime);

DECLARE_CRT_EXPORT("FileTimeToSystemTime", FileTimeToSystemTime);
