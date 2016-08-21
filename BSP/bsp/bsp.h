#ifndef _BSP_H
#define _BSP_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "timer.h"
#include "debug_gpio.h"
#include "timer_core.h"
#include "comm_rec.h"
#include "delay.h"
#include "key.h"
#include "debug_uart.h"
#include "digital.h"
#include "pub.h"

//NVIC中断优先级组默认为组2
#define SYS_GROUP_PRIORITY NVIC_PriorityGroup_2

void BSP_Init(void);


#endif
