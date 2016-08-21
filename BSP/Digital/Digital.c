#include "digital.h"


//按键数据结构
_DEF_UINT16_BIT Digital;
_DEF_UINT8_BIT  Digit;

/*-----------------------------------------------------------
** 功能描述: 按键端口初始化
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void DIGITAL_Init(void)
{
    Pub_Gpio_Output_OUTPP(GPIOA,DIGITAL0_GPIO_Pin | DIGITAL1_GPIO_Pin | DIGITAL2_GPIO_Pin | DIGITAL3_GPIO_Pin | 
                             DIGITAL4_GPIO_Pin | DIGITAL5_GPIO_Pin | DIGITAL6_GPIO_Pin | DIGITAL7_GPIO_Pin );
    
    Pub_Gpio_Output_OUTPP(GPIOB,COMM0_GPIO_Pin | COMM1_GPIO_Pin | COMM2_GPIO_Pin | COMM3_GPIO_Pin | COMM4_GPIO_Pin);
}

/*-----------------------------------------------------------
** 功能描述: 读按键端口
** 入口参数: 无
** 出口参数: KeyBoard.Val :按键值
-------------------------------------------------------------*/
void LOAD_DIGITAL(u8 bit,u16 val)
{
    Digital.Val = val;
    DIGITAL0_VAL = Digital.Bit.b0;
    DIGITAL1_VAL = Digital.Bit.b1;
    DIGITAL2_VAL = Digital.Bit.b2;
    DIGITAL3_VAL = Digital.Bit.b3;
    DIGITAL4_VAL = Digital.Bit.b4;
    DIGITAL5_VAL = Digital.Bit.b5;
    DIGITAL6_VAL = Digital.Bit.b6;
    DIGITAL7_VAL = Digital.Bit.b7;
    
    Digit.Val = bit;
    
    COMM0_VAL = Digit.Bit.b0;
    COMM1_VAL = Digit.Bit.b1;
    COMM2_VAL = Digit.Bit.b2;
    COMM3_VAL = Digit.Bit.b3;
    COMM4_VAL = Digit.Bit.b4;
}

