#ifndef _DEBUG_GPIO_H
#define _DEBUG_GPIO_H

#include "pub.h"

//Ĭ��DEBUG��Ϊ���������
#define DEBUG_GPIO          PEout(5)

#define DEBUG_GPIOx         GPIOE
#define DEBUG_GPIOx_PIN     GPIO_Pin_5

void Debug_Gpio_Init(void);
void Debug_Gpio_SetBit(void);
void Debug_Gpio_ResetBit(void);

#endif
