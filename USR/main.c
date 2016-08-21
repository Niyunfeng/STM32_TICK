#define _SYSTEM_C
#include "system.h"

void sys_tick(void)
{
    DEBUG_GPIO = !DEBUG_GPIO;
}

void uart_decode(void *msg)
{
    pCOMM_REC_STRUCT p_data = (pCOMM_REC_STRUCT)msg;
    Usart_SendBuf(p_data->Buf, p_data->Index);
}

int main(void)
{
    BSP_Init();
    
    Sys.Comm[0] = CommRec_Create(1, 15, (Func_Rec)Usart_RecvData, (Func_Rec_Fin)uart_decode, (Func_Rec_Fin)NULL);

    Sys.Tick[0] = LBTIM_Create(ENABLE, 1000, (FUNC_TIMER)0, (FUNC_TIMER)sys_tick, (void *)0);

    while (1)
    {
        LBTIM_Exc();
    }
}
