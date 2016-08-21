#include "key.h"

//�������ݽṹ
_DEF_UINT16_BIT KeyBoard;

/*-----------------------------------------------------------
** ��������: �����˿ڳ�ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
void Key_Init(void)
{
    Pub_Gpio_Input_IPU(KEY0_GPIOx,KEY0_GPIO_Pin | KEY1_GPIO_Pin | KEY2_GPIO_Pin | KEY3_GPIO_Pin | 
                                  KEY4_GPIO_Pin | KEY5_GPIO_Pin | KEY6_GPIO_Pin | KEY7_GPIO_Pin );
}

/*-----------------------------------------------------------
** ��������: �������˿�
** ��ڲ���: ��
** ���ڲ���: KeyBoard.Val :����ֵ
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
** ��������: ���������������
** ��ڲ���: num�����尴��ֵ
** ���ڲ���: ��
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
** ��������: ����ɨ�����
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
void Key_Scan(void)
{
    static u8 key_flag = 1;                     //key_flag�������ɿ���־λ
    if(KEY_MODE) key_flag = 1;                  //KEY_MODE�������������Ͳ�������ģʽλ
    if(key_flag && (Read_KeyPort() != 0xff))    //�ж��Ƿ��а������£�������״̬��key_flag��Ϊ1����һֱ��������ֵ
    {                                           //������״̬��key_flag���ɿ�ǰ��״̬���ԣ����û���ɿ�key_flag��Ϊ0���˳�ɨ�����
        Delay_Ms(10);
        key_flag = 0;
        if(Read_KeyPort() != 0xff)              //����
        {
            Key_Exc(KeyBoard.Val);              //ִ�а����������
            return;
        }
    }
    else if(Read_KeyPort() == 0xff)             //û�а����������־λ��λ
    {
        key_flag = 1;
    }
}


