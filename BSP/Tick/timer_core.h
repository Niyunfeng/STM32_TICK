#ifndef _TIMER_CORE_H
#define _TIMER_CORE_H

#ifdef _TIMER_CORE_C
    #define TIMER_CORE_EXT
#else
    #define TIMER_CORE_EXT extern
#endif

#include "pub.h"

#define TIMER_NUM   10					    //软件定时器最大个数

typedef void (*FUNC_TIMER)(void *MSG);	    //函数指针

typedef struct
{
	void 		    *Msg;					//传入参数
    vu32 		    Cnt;					//溢出计数器
	vu32		    Interval;				//定时间隔
	FunctionalState	State;					//定时器状态
	FlagStatus	    Flag;					//标志位
    FUNC_TIMER      FCallBack;				//中断外回调函数
	FUNC_TIMER	    FCallBackInt;			//中断内回调函数
}TIMER_STRUCT,*pTIMER_STRUCT;

TIMER_CORE_EXT TIMER_STRUCT Timer[TIMER_NUM];//软件定时器实体

TIMER_CORE_EXT void LBTIM_Init(void);	    //初始化软件定时器
TIMER_CORE_EXT void LBTIM_Tick(void);	    //软件定时器滴答
TIMER_CORE_EXT void LBTIM_Exc(void);	    //软件定时器溢出执行
TIMER_CORE_EXT TIMER_STRUCT * LBTIM_Create(FunctionalState State,
							vu32 Interval,
							FUNC_TIMER FcallBack,
							FUNC_TIMER FcallBackInt,
							void *msg);	    //创建软件定时器
TIMER_CORE_EXT void LBTIM_Config(TIMER_STRUCT *TIMx,FunctionalState State);	//配置软件定时器状态
TIMER_CORE_EXT void LBTIM_Enable(TIMER_STRUCT *TIMx);					    //开启软件定时器
TIMER_CORE_EXT void LBTIM_Disable(TIMER_STRUCT *TIMx);					    //关闭软件定时器
TIMER_CORE_EXT void LBTIM_ClearCnt(TIMER_STRUCT *TIMx);					    //复位定时时间
TIMER_CORE_EXT void LBTIM_TimeBase(TIMER_STRUCT *TIMx,vu32 Interval);	    //配置软件定时器定时间隔

TIMER_CORE_EXT vu8 LBTIM_GetTimNum(void);								    //获得已创建定时器个数
#endif
