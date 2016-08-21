#ifndef _COMM_REC_H
#define _COMM_REC_H

#include "timer_core.h"

#ifdef _COMM_REC_C
    #define COMM_REC_EXT
#else 
    #define COMM_REC_EXT extern
#endif 

#define COMM_REC_NUM    3
#define RECVBUF_MAXNUM     255

typedef uint16_t (*Func_Rec)(void);      //º¯ÊýÖ¸Õë
typedef void     (*Func_Rec_Fin)(void *msg);

typedef struct
{
    u8              Addr;
    u8              Index;
    u8              *Buf;
    u8              MaxNum;
    FlagStatus      Flag;
    pTIMER_STRUCT   Timer;
    Func_Rec        FCommRec;
    Func_Rec_Fin    FCommRecFin;
    Func_Rec_Fin    FCommRecFinInt;
}COMM_REC_STRUCT,*pCOMM_REC_STRUCT;

void CommRec_Init(void);
pCOMM_REC_STRUCT CommRec_Create(u8 Addr,
                                u8 MaxNum,
                                Func_Rec FCommRec,
                                Func_Rec_Fin FCommRecFin,
                                Func_Rec_Fin FCommRecFinInt);
void USART_Recv_Handle(pCOMM_REC_STRUCT p_data);

#endif

