#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <search.h>
#include <assert.h>

#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"
#include "log.h"
#include "winexports.h"
#include "util.h"
#include "strings.h"

STATIC DWORD WINAPI CoCreateGuid(PVOID pguid)
{
    NOP_FILL();
    DebugLog("%p", pguid);
    memcpy(pguid, "GUIDGUIDGUIDGUIDGUIDGUIDGUIDGUID", 16);
    return 0;
}

STATIC DWORD CoCreateInstance(PVOID rclsid, PVOID pUnkOuter, DWORD dwClsContext, PVOID riid, PVOID *ppv)
{
    NOP_FILL();
    DebugLog("%p, %p, %u, %p, %p", rclsid, pUnkOuter, dwClsContext, riid, ppv);
    return -1;
}

STATIC DWORD CoInitializeEx(PVOID pvReserved, DWORD dCwoInit)
{
    NOP_FILL();
    DebugLog("%p, %u", pvReserved, dCwoInit);
    return -1;
}

STATIC DWORD CoSetProxyBlanket(PVOID a)
{
    NOP_FILL();
    DebugLog("");
    return -1;
}

STATIC DWORD CoUninitialize(PVOID a)
{
    NOP_FILL();
    DebugLog("");
    return -1;
}

STATIC DWORD IIDFromString(PVOID a)
{
    NOP_FILL();
    DebugLog("");
    return -1;
}

DECLARE_CRT_EXPORT("CoCreateGuid", CoCreateGuid, 1);
DECLARE_CRT_EXPORT("CoCreateInstance", CoCreateInstance, 5);
DECLARE_CRT_EXPORT("CoInitializeEx", CoInitializeEx, 2);
DECLARE_CRT_EXPORT("CoSetProxyBlanket", CoSetProxyBlanket, 1);
DECLARE_CRT_EXPORT("CoUninitialize", CoUninitialize, 1);
DECLARE_CRT_EXPORT("IIDFromString", IIDFromString, 1);
