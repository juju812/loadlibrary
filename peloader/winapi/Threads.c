#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <search.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"
#include "log.h"
#include "winexports.h"
#include "util.h"
#include "winstrings.h"

static __stdcall PVOID CreateThreadPoolWait(PVOID pwa)
{
    NOP_FILL();
    DebugLog("");
    return (PVOID) 0x41414141;
}

static __stdcall PVOID CreateThreadPool(PVOID reserved)
{
    NOP_FILL();
    DebugLog("");
    return (PVOID) 0x41414141;
}

static __stdcall PVOID CreateThreadpoolTimer(PVOID pfnti, PVOID pv, PVOID pcbe)
{
    NOP_FILL();
    DebugLog("");
    return (PVOID) 0x41414141;
}

static __stdcall PVOID CreateThreadpoolWork(PVOID pfnwk, PVOID pv, PVOID pcbe)
{
    NOP_FILL();
    DebugLog("");
    return (PVOID) 0x41414141;
}

static __stdcall void CloseThreadpoolTimer(PVOID pti)
{
    NOP_FILL();
    DebugLog("%p", pti);
}

static __stdcall void InitializeConditionVariable(PVOID ConditionVariable)
{
    NOP_FILL();
    DebugLog("%p", ConditionVariable);
}

static __stdcall BOOL SleepConditionVariableCS(PVOID ConditionVariable,
                                               PVOID CriticalSection,
                                               DWORD dwMilliseconds)
{
    NOP_FILL();
    DebugLog("%p %p %u", ConditionVariable, CriticalSection, dwMilliseconds);
    return TRUE;
}

static __stdcall void WakeAllConditionVariable(PVOID ConditionVariable)
{
    NOP_FILL();
    DebugLog("%p", ConditionVariable);
}


static __stdcall PVOID CreateThreadpoolWait() { NOP_FILL(); DebugLog(""); return NULL; }
static __stdcall PVOID SetThreadpoolWait() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID SubmitThreadpoolWork() {NOP_FILL(); DebugLog(""); return NULL; }
static __stdcall PVOID CancelThreadpoolIo() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID CloseThreadpool() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID CloseThreadpoolIo() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID CloseThreadpoolWait() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall void CloseThreadpoolWork(PVOID pwk)
{
    NOP_FILL();
    DebugLog("%p", pwk);
}
static __stdcall PVOID CreateThreadpool() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID CreateThreadpoolIo() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID SetThreadpoolThreadMaximum() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID SetThreadpoolThreadMinimum() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID StartThreadpoolIo() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID WaitForThreadpoolIoCallbacks() { NOP_FILL();DebugLog(""); return NULL; }
static __stdcall PVOID WaitForThreadpoolWaitCallbacks() { NOP_FILL();DebugLog(""); return NULL; }

static __stdcall void WaitForThreadpoolWorkCallbacks(PVOID pwk, BOOL fCancelPendingCallbacks)
{
    NOP_FILL();
    DebugLog("%p %d", pwk, fCancelPendingCallbacks);
}


DECLARE_CRT_EXPORT("CreateThreadPoolWait", CreateThreadPoolWait, 1);
DECLARE_CRT_EXPORT("CreateThreadPool", CreateThreadPool, 1);
DECLARE_CRT_EXPORT("InitializeConditionVariable", InitializeConditionVariable, 1);
DECLARE_CRT_EXPORT("SleepConditionVariableCS", SleepConditionVariableCS, 3);
DECLARE_CRT_EXPORT("WakeAllConditionVariable", WakeAllConditionVariable, 1);

DECLARE_CRT_EXPORT("CreateThreadpoolTimer", CreateThreadpoolTimer, 3);
DECLARE_CRT_EXPORT("CloseThreadpoolTimer", CloseThreadpoolTimer, 1);
DECLARE_CRT_EXPORT("CreateThreadpoolWait", CreateThreadpoolWait, 0);
DECLARE_CRT_EXPORT("SetThreadpoolWait", SetThreadpoolWait, 0);
DECLARE_CRT_EXPORT("CloseThreadpoolWait", CloseThreadpoolWait, 0);
DECLARE_CRT_EXPORT("CreateThreadpoolWork", CreateThreadpoolWork, 0);
DECLARE_CRT_EXPORT("SubmitThreadpoolWork", SubmitThreadpoolWork, 0);
DECLARE_CRT_EXPORT("CancelThreadpoolIo", CancelThreadpoolIo, 0);
DECLARE_CRT_EXPORT("CloseThreadpool", CloseThreadpool, 0);
DECLARE_CRT_EXPORT("CloseThreadpoolIo", CloseThreadpoolIo, 0);
DECLARE_CRT_EXPORT("CloseThreadpoolWork", CloseThreadpoolWork, 1);
DECLARE_CRT_EXPORT("CreateThreadpool", CreateThreadpool, 0);
DECLARE_CRT_EXPORT("CreateThreadpoolIo", CreateThreadpoolIo, 0);
DECLARE_CRT_EXPORT("SetThreadpoolThreadMaximum", SetThreadpoolThreadMaximum, 0);
DECLARE_CRT_EXPORT("SetThreadpoolThreadMinimum", SetThreadpoolThreadMinimum, 0);
DECLARE_CRT_EXPORT("StartThreadpoolIo", StartThreadpoolIo, 0);
DECLARE_CRT_EXPORT("WaitForThreadpoolIoCallbacks", WaitForThreadpoolIoCallbacks, 0);
DECLARE_CRT_EXPORT("WaitForThreadpoolWaitCallbacks", WaitForThreadpoolWaitCallbacks, 0);
DECLARE_CRT_EXPORT("WaitForThreadpoolWorkCallbacks", WaitForThreadpoolWorkCallbacks, 2);
