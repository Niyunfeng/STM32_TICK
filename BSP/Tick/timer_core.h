#ifndef _TIMER_CORE_H
#define _TIMER_CORE_H

#ifdef _TIMER_CORE_C
    #define TIMER_CORE_EXT
#else
    #define TIMER_CORE_EXT extern
#endif

#include "pub.h"

#define TIMER_NUM   10					    //�����ʱ��������

typedef void (*FUNC_TIMER)(void *MSG);	    //����ָ��

typedef struct
{
	void 		    *Msg;					//�������
    vu32 		    Cnt;					//���������
	vu32		    Interval;				//��ʱ���
	FunctionalState	State;					//��ʱ��״̬
	FlagStatus	    Flag;					//��־λ
    FUNC_TIMER      FCallBack;				//�ж���ص�����
	FUNC_TIMER	    FCallBackInt;			//�ж��ڻص�����
}TIMER_STRUCT,*pTIMER_STRUCT;

TIMER_CORE_EXT TIMER_STRUCT Timer[TIMER_NUM];//�����ʱ��ʵ��

TIMER_CORE_EXT void LBTIM_Init(void);	    //��ʼ�������ʱ��
TIMER_CORE_EXT void LBTIM_Tick(void);	    //�����ʱ���δ�
TIMER_CORE_EXT void LBTIM_Exc(void);	    //�����ʱ�����ִ��
TIMER_CORE_EXT TIMER_STRUCT * LBTIM_Create(FunctionalState State,
							vu32 Interval,
							FUNC_TIMER FcallBack,
							FUNC_TIMER FcallBackInt,
							void *msg);	    //���������ʱ��
TIMER_CORE_EXT void LBTIM_Config(TIMER_STRUCT *TIMx,FunctionalState State);	//���������ʱ��״̬
TIMER_CORE_EXT void LBTIM_Enable(TIMER_STRUCT *TIMx);					    //���������ʱ��
TIMER_CORE_EXT void LBTIM_Disable(TIMER_STRUCT *TIMx);					    //�ر������ʱ��
TIMER_CORE_EXT void LBTIM_ClearCnt(TIMER_STRUCT *TIMx);					    //��λ��ʱʱ��
TIMER_CORE_EXT void LBTIM_TimeBase(TIMER_STRUCT *TIMx,vu32 Interval);	    //���������ʱ����ʱ���

TIMER_CORE_EXT vu8 LBTIM_GetTimNum(void);								    //����Ѵ�����ʱ������
#endif
