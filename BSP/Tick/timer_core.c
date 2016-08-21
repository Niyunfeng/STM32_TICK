#define _TIMER_CORE_C
#include "timer_core.h"

static vu8 TimerAlloc;	//�����ʱ��������

/*-----------------------------------------------------------
** ��������: ��ʱ���ؼ���������ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_Init(void)
{
    vu8 i;
    
    TimerAlloc = 0;
    
	for(i=0; i<TIMER_NUM; i++)
	{
		Timer[i].Cnt        = 0;			
		Timer[i].Flag       = RESET;		
        Timer[i].Interval   = 0;			
        Timer[i].State      = DISABLE;
	}
}

/*-----------------------------------------------------------
** ��������: ���������ʱ��
** ��ڲ���: State			:�����ʱ������״̬
			 Interval		:�����ʱ����ʱ���
			 FcallBack		:�ж���ص�����
			 FcallBackInt	:�ж��ڻص�����
			 msg			:�������
** ���ڲ���: ��
---------------------------------------------------------------*/
TIMER_STRUCT * LBTIM_Create(FunctionalState State,
							vu32 Interval,
							FUNC_TIMER FcallBack,
							FUNC_TIMER FcallBackInt,
							void *msg)
{
	if(TimerAlloc >= TIMER_NUM)
	{
		return NULL;
	}
	
    Timer[TimerAlloc].Interval     	= Interval;
    Timer[TimerAlloc].State	    	= State;
    Timer[TimerAlloc].FCallBack    	= FcallBack;
	Timer[TimerAlloc].Msg			= msg;
	Timer[TimerAlloc].FCallBackInt 	= FcallBackInt;
	
	TimerAlloc++;
	
	return	&Timer[TimerAlloc-1];
}

/*-----------------------------------------------------------
** ��������: �����ʱ����ʱִ��
** ��ڲ���: ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_Exc(void)
{
    vu8 i;
    for(i=0; i<TIMER_NUM; i++)
	{
	    if(Timer[i].Flag == SET)
		{
			Timer[i].Flag = RESET;
			if(Timer[i].FCallBack != NULL)
			{
				Timer[i].FCallBack(Timer[i].Msg);
			}
		}	
	}
}

/*-----------------------------------------------------------
** ��������: �����ʱ���δ�
** ��ڲ���: ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_Tick(void)
{
	vu8 i;
	for (i=0; i<TIMER_NUM; i++)
	{
		if(Timer[i].State == ENABLE)
		{
			Timer[i].Cnt++;
			if(Timer[i].Cnt >= Timer[i].Interval)
			{
				Timer[i].Cnt = 0;
				if(Timer[i].Flag == RESET)
				{
					Timer[i].Flag = SET;
					if(Timer[i].FCallBackInt != NULL)
					{
						Timer[i].FCallBackInt(Timer[i].Msg);
					}
				}
			}	
		}
	} 
}

/*-----------------------------------------------------------
** ��������: �����ʱ��״̬����
** ��ڲ���: TIMx	:��Ӧ�����ʱ��
			 State	:�����ʱ������״̬
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_Config(TIMER_STRUCT *TIMx,FunctionalState State)
{
	TIMx->State = State;
}

/*-----------------------------------------------------------
** ��������: ���������ʱ��
** ��ڲ���: TIMx	:��Ӧ�����ʱ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_Enable(TIMER_STRUCT *TIMx)
{
	TIMx->State = ENABLE;
}

/*-----------------------------------------------------------
** ��������: �ر������ʱ��
** ��ڲ���: TIMx	:��Ӧ�����ʱ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_Disable(TIMER_STRUCT *TIMx)
{
	TIMx->State = DISABLE;
}

/*-----------------------------------------------------------
** ��������: ���������ʱ����ʱʱ��
** ��ڲ���: TIMx	:��Ӧ�����ʱ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_ClearCnt(TIMER_STRUCT *TIMx)
{
	TIMx->Cnt = 0;
}

/*-----------------------------------------------------------
** ��������: ���������ʱ����ʱ���ʱ��
** ��ڲ���: TIMx	:��Ӧ�����ʱ��
** ���ڲ���: ��
---------------------------------------------------------------*/
void LBTIM_TimeBase(TIMER_STRUCT *TIMx,vu32 Interval)
{
	TIMx->Interval = Interval;
}

/*-----------------------------------------------------------
** ��������: ��ȡ�����ʱ������
** ��ڲ���: ��
** ���ڲ���: TimerAlloc:��ǰ�����ʱ������
---------------------------------------------------------------*/
vu8 LBTIM_GetTimNum(void)
{
	return TimerAlloc;
}
