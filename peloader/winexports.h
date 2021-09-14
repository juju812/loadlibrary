#pragma once
#ifndef __WINEXPORTS_H
#define __WINEXPORTS_H

#ifdef __APPLE__
#include "hsearch_r.h"
#else
#include <search.h>
#endif

extern struct hsearch_data crtexports;
#define MAX_CRT_EXPORTS 65535

#define DECLARE_CRT_EXPORT(_name, _func)                 \
    static void __constructor __const__ ## _func (void)  \
    {                                                    \
        ENTRY e = { _name, _func }, *ep;                 \
        if (crtexports.table == NULL)                    \
            hcreate_r(MAX_CRT_EXPORTS, &crtexports);                \
        hsearch_r(e, ENTER, &ep, &crtexports);           \
        return;                                          \
    }

#endif
