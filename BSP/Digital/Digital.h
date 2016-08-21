#ifndef __DIGITAL_H
#define __DIGITAL_H

#include "system.h"

//默认支持8个独立按键
//按键默认端口模式为上拉/下拉输入
#define DIGITAL0_GPIOx      GPIOA  
#define DIGITAL0_GPIO_Pin   GPIO_Pin_0
        
#define DIGITAL1_GPIOx      GPIOA  
#define DIGITAL1_GPIO_Pin   GPIO_Pin_1
        
#define DIGITAL2_GPIOx      GPIOA  
#define DIGITAL2_GPIO_Pin   GPIO_Pin_2
        
#define DIGITAL3_GPIOx      GPIOA  
#define DIGITAL3_GPIO_Pin   GPIO_Pin_3
        
#define DIGITAL4_GPIOx      GPIOA  
#define DIGITAL4_GPIO_Pin   GPIO_Pin_4
        
#define DIGITAL5_GPIOx      GPIOA  
#define DIGITAL5_GPIO_Pin   GPIO_Pin_5
        
#define DIGITAL6_GPIOx      GPIOA  
#define DIGITAL6_GPIO_Pin   GPIO_Pin_6
        
#define DIGITAL7_GPIOx      GPIOA  
#define DIGITAL7_GPIO_Pin   GPIO_Pin_7

#define COMM0_GPIOx         GPIOB
#define COMM0_GPIO_Pin      GPIO_Pin_5

#define COMM1_GPIOx         GPIOB
#define COMM1_GPIO_Pin      GPIO_Pin_6

#define COMM2_GPIOx         GPIOB
#define COMM2_GPIO_Pin      GPIO_Pin_7

#define COMM3_GPIOx         GPIOB
#define COMM3_GPIO_Pin      GPIO_Pin_10

#define COMM4_GPIOx         GPIOB
#define COMM4_GPIO_Pin      GPIO_Pin_9

#define DIGITAL0_VAL        PAout(0)
#define DIGITAL1_VAL        PAout(1)
#define DIGITAL2_VAL        PAout(2)
#define DIGITAL3_VAL        PAout(3)
#define DIGITAL4_VAL        PAout(4)
#define DIGITAL5_VAL        PAout(5)
#define DIGITAL6_VAL        PAout(6)
#define DIGITAL7_VAL        PAout(7)

#define COMM0_VAL           PBout(5)    
#define COMM1_VAL           PBout(6)  
#define COMM2_VAL           PBout(7)  
#define COMM3_VAL           PBout(10)  
#define COMM4_VAL           PBout(9)  

void DIGITAL_Init(void);
void LOAD_DIGITAL(u8 bit,u16 val);


#endif
