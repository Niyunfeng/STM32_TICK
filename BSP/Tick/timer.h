#ifndef __TIMER_H
#define __TIMER_H

#include "pub.h"
#include "debug_gpio.h"
#include "timer_core.h"

#define TICK_TIMER              TIM3                //选择具体定时器来产生TICK
#define TICK_TIMER_IRQ          TIM3_IRQn           //定时器中断号
#define TICK_TIMER_IRQHandler   TIM3_IRQHandler     //定时器中断入口地址
#define RCC_APB1Periph_TIMx     RCC_APB1Periph_TIM3 //定义定时器时钟

#define TICK_PER_SECOND         1000                //系统时间片，系统运行频率1000HZ     取值范围 1~1000

void TIME_Tick_Init(void);

#endif
