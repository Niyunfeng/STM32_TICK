#define _TIMER_CORE_C
#include "timer_core.h"

static vu8 TimerAlloc;	//软件定时器计数器

/*-----------------------------------------------------------
** 功能描述: 定时器控件各参数初始化
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 创建软件定时器
** 入口参数: State			:软件定时器开关状态
			 Interval		:软件定时器定时间隔
			 FcallBack		:中断外回调函数
			 FcallBackInt	:中断内回调函数
			 msg			:传入参数
** 出口参数: 无
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
** 功能描述: 软件定时器定时执行
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 软件定时器滴答
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 软件定时器状态配置
** 入口参数: TIMx	:对应软件定时器
			 State	:软件定时器开关状态
** 出口参数: 无
---------------------------------------------------------------*/
void LBTIM_Config(TIMER_STRUCT *TIMx,FunctionalState State)
{
	TIMx->State = State;
}

/*-----------------------------------------------------------
** 功能描述: 开启软件定时器
** 入口参数: TIMx	:对应软件定时器
** 出口参数: 无
---------------------------------------------------------------*/
void LBTIM_Enable(TIMER_STRUCT *TIMx)
{
	TIMx->State = ENABLE;
}

/*-----------------------------------------------------------
** 功能描述: 关闭软件定时器
** 入口参数: TIMx	:对应软件定时器
** 出口参数: 无
---------------------------------------------------------------*/
void LBTIM_Disable(TIMER_STRUCT *TIMx)
{
	TIMx->State = DISABLE;
}

/*-----------------------------------------------------------
** 功能描述: 清零软件定时器定时时间
** 入口参数: TIMx	:对应软件定时器
** 出口参数: 无
---------------------------------------------------------------*/
void LBTIM_ClearCnt(TIMER_STRUCT *TIMx)
{
	TIMx->Cnt = 0;
}

/*-----------------------------------------------------------
** 功能描述: 设置软件定时器定时间隔时间
** 入口参数: TIMx	:对应软件定时器
** 出口参数: 无
---------------------------------------------------------------*/
void LBTIM_TimeBase(TIMER_STRUCT *TIMx,vu32 Interval)
{
	TIMx->Interval = Interval;
}

/*-----------------------------------------------------------
** 功能描述: 获取软件定时器个数
** 入口参数: 无
** 出口参数: TimerAlloc:当前软件定时器个数
---------------------------------------------------------------*/
vu8 LBTIM_GetTimNum(void)
{
	return TimerAlloc;
}
