#ifndef __KEY_H
#define __KEY_H

#include "pub.h"
#include "delay.h"
#include "debug_gpio.h"
#include "timer_core.h"
#include "system.h"

//默认支持8个独立按键
//按键默认端口模式为上拉/下拉输入
#define KEY0_GPIOx      GPIOA  
#define KEY0_GPIO_Pin   GPIO_Pin_0

#define KEY1_GPIOx      GPIOA  
#define KEY1_GPIO_Pin   GPIO_Pin_1

#define KEY2_GPIOx      GPIOA  
#define KEY2_GPIO_Pin   GPIO_Pin_2

#define KEY3_GPIOx      GPIOA  
#define KEY3_GPIO_Pin   GPIO_Pin_3

#define KEY4_GPIOx      GPIOA  
#define KEY4_GPIO_Pin   GPIO_Pin_4

#define KEY5_GPIOx      GPIOA  
#define KEY5_GPIO_Pin   GPIO_Pin_5

#define KEY6_GPIOx      GPIOA  
#define KEY6_GPIO_Pin   GPIO_Pin_6

#define KEY7_GPIOx      GPIOA  
#define KEY7_GPIO_Pin   GPIO_Pin_7

#define KEY0_VAL        PAin(0)
#define KEY1_VAL        PAin(1)
#define KEY2_VAL        PAin(2)
#define KEY3_VAL        PAin(3)
#define KEY4_VAL        PAin(4)
#define KEY5_VAL        PAin(5)
#define KEY6_VAL        PAin(6)
#define KEY7_VAL        PAin(7)

#define KEY_MODE 1  //按键模式选择  0:不支持连续按  1:支持连续按

void Key_Init(void);
void Key_Scan(void);

#endif
