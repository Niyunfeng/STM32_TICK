#include "key.h"

//按键数据结构
_DEF_UINT16_BIT KeyBoard;

/*-----------------------------------------------------------
** 功能描述: 按键端口初始化
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void Key_Init(void)
{
    Pub_Gpio_Input_IPU(KEY0_GPIOx,KEY0_GPIO_Pin | KEY1_GPIO_Pin | KEY2_GPIO_Pin | KEY3_GPIO_Pin | 
                                  KEY4_GPIO_Pin | KEY5_GPIO_Pin | KEY6_GPIO_Pin | KEY7_GPIO_Pin );
}

/*-----------------------------------------------------------
** 功能描述: 读按键端口
** 入口参数: 无
** 出口参数: KeyBoard.Val :按键值
-------------------------------------------------------------*/
static u16 Read_KeyPort(void)
{
    KeyBoard.Bit.b0  = KEY0_VAL;
    KeyBoard.Bit.b1  = KEY1_VAL;
    KeyBoard.Bit.b2  = KEY2_VAL;
    KeyBoard.Bit.b3  = KEY3_VAL;
    KeyBoard.Bit.b4  = KEY4_VAL;
    KeyBoard.Bit.b5  = KEY5_VAL;
    KeyBoard.Bit.b6  = KEY6_VAL;
    KeyBoard.Bit.b7  = KEY7_VAL;
    KeyBoard.Bit.b8  = 0;
    KeyBoard.Bit.b9  = 0;
    KeyBoard.Bit.b10 = 0;
    KeyBoard.Bit.b11 = 0;
    KeyBoard.Bit.b12 = 0;
    KeyBoard.Bit.b13 = 0;
    KeyBoard.Bit.b14 = 0;
    KeyBoard.Bit.b15 = 0;
    return KeyBoard.Val;
}

/*-----------------------------------------------------------
** 功能描述: 按键触发处理程序
** 入口参数: num：具体按键值
** 出口参数: 无
-------------------------------------------------------------*/
void Key_Exc(u16 num)
{
    switch(num)
    {
        case 0xff:  break;
        
        case 0xfe:  break;
        case 0xfd:  break;
        case 0xfb:  break;
        case 0xf7:  break;
        
        case 0xef:  break;
        case 0xdf:  break;
        case 0xbf:  break;
        case 0x7f:  break;
    }
}

/*-----------------------------------------------------------
** 功能描述: 按键扫描程序
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void Key_Scan(void)
{
    static u8 key_flag = 1;                     //key_flag：按键松开标志位
    if(KEY_MODE) key_flag = 1;                  //KEY_MODE：按键连续按和不连续按模式位
    if(key_flag && (Read_KeyPort() != 0xff))    //判断是否有按键按下，连续按状态下key_flag恒为1，会一直触发按键值
    {                                           //不连续状态下key_flag由松开前的状态绝对，如果没有松开key_flag则为0，退出扫描程序
        Delay_Ms(10);
        key_flag = 0;
        if(Read_KeyPort() != 0xff)              //消抖
        {
            Key_Exc(KeyBoard.Val);              //执行按键处理程序
            return;
        }
    }
    else if(Read_KeyPort() == 0xff)             //没有按键按下则标志位置位
    {
        key_flag = 1;
    }
}


