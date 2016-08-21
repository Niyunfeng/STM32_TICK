#define _COMM_REC_C
#include "comm_rec.h"

//串口控件个数
static u8 CommRecAlloc;
static COMM_REC_STRUCT CommRecData[COMM_REC_NUM];

//串口接收缓冲区大小
static u8 BufAlloc;         
static u8 CommRecBuf[RECVBUF_MAXNUM];

static void CommRec_Struct_Init(void)
{
    CommRecAlloc = 0;
    BufAlloc = 0;
}

void USART_Recv_Handle(pCOMM_REC_STRUCT p_data)
{
    LBTIM_Enable(p_data->Timer);
    LBTIM_ClearCnt(p_data->Timer);
    
    //防止数据没处理完就进行下一次接收
    if(p_data->Flag == RESET)
    {
        p_data->Buf[p_data->Index] = p_data->FCommRec();
        p_data->Index++;
        
        if(p_data->Index >= p_data->MaxNum)
        {
            p_data->Index = p_data->MaxNum;
        }
    }
}

static void CommRec_Fin(void *msg)
{
    pCOMM_REC_STRUCT p_data = (pCOMM_REC_STRUCT)msg;
    
    LBTIM_Disable(p_data->Timer);
    //数据开始处理
    if(p_data->FCommRecFin == NULL)
	{
        return;
    }
    
    p_data->Flag = SET;
    
    if(p_data->Buf[0] == p_data->Addr)
    {
        p_data->FCommRecFin((void*)p_data);
    }
    p_data->Index = 0;
    //数据处理完成
    p_data->Flag = RESET;
}


void CommRec_Init(void)
{
    CommRec_Struct_Init();
}

pCOMM_REC_STRUCT CommRec_Create(u8 Addr,
                                u8 MaxNum,
                                Func_Rec FCommRec,
                                Func_Rec_Fin FCommRecFin,
                                Func_Rec_Fin FCommRecFinInt)
{
    pCOMM_REC_STRUCT p_data;
    p_data = CommRecData;
    
    if(CommRecAlloc >= COMM_REC_NUM)    
    {
        return NULL;
    }
    else    
    {
        p_data = &CommRecData[CommRecAlloc];
        CommRecAlloc++;
    }
    
    if((BufAlloc + MaxNum) <= RECVBUF_MAXNUM)
    {
        p_data->Buf = &CommRecBuf[BufAlloc];
        BufAlloc += MaxNum;
        p_data->MaxNum = MaxNum;
    }
    else
    {
        return NULL;
    }
    
    p_data->Addr            = Addr;
    p_data->Flag            = RESET;
    p_data->FCommRec        = FCommRec;
    p_data->FCommRecFin     = FCommRecFin;
    p_data->FCommRecFinInt  = FCommRecFinInt;
    
    p_data->Timer = LBTIM_Create(DISABLE,3,(FUNC_TIMER)CommRec_Fin,(FUNC_TIMER)NULL,(void *)p_data);
    
    p_data->Index = 0;
    
    return p_data;
}






