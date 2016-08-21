#ifndef __TIMER_H
#define __TIMER_H

#include "pub.h"
#include "debug_gpio.h"
#include "timer_core.h"

#define TICK_TIMER              TIM3                //ѡ����嶨ʱ��������TICK
#define TICK_TIMER_IRQ          TIM3_IRQn           //��ʱ���жϺ�
#define TICK_TIMER_IRQHandler   TIM3_IRQHandler     //��ʱ���ж���ڵ�ַ
#define RCC_APB1Periph_TIMx     RCC_APB1Periph_TIM3 //���嶨ʱ��ʱ��

#define TICK_PER_SECOND         1000                //ϵͳʱ��Ƭ��ϵͳ����Ƶ��1000HZ     ȡֵ��Χ 1~1000

void TIME_Tick_Init(void);

#endif
