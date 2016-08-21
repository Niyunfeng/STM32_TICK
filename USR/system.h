#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "bsp.h"

#ifdef _SYSTEM_C
    #define SYSTEM_EXT
#else
    #define SYSTEM_EXT extern
#endif

#define TICK_MAXNUM 10
#define COMM_MAXNUM 3

typedef struct
{
    pTIMER_STRUCT    Tick[TICK_MAXNUM];
    pCOMM_REC_STRUCT Comm[COMM_MAXNUM];
}_SYS_DEF;

SYSTEM_EXT _SYS_DEF Sys;

#endif
