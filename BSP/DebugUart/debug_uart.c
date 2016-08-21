#include "debug_uart.h"

static void Usart1_Init(void);
static void Usart2_Init(void);
static void Usart3_Init(void);

/*-----------------------------------------------------------
** ��������: ���Դ��ڳ�ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
void Debug_Uart_Init(void)
{
    USART_DeInit(DEBUG_UARTx);
    if(DEBUG_UARTx == USART1)       Usart1_Init();
    else if(DEBUG_UARTx == USART2)  Usart2_Init();
    else if(DEBUG_UARTx == USART3)  Usart3_Init();
}

/*-----------------------------------------------------------
** ��������: ����1��ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
static void Usart1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
    Pub_Gpio_Output_AFPP(GPIOA, GPIO_Pin_9);
    Pub_Gpio_Input_INFLOATING(GPIOA, GPIO_Pin_10);
    Pub_Uart_Hardware_Cfg(USART1,DEBUG_UARTx_BAUD);
    Pub_Nvic_Config(USART1_IRQn, 0, 0);
    Pub_Uart_Int_Cfg(USART1);
}

/*-----------------------------------------------------------
** ��������: ����2��ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
static void Usart2_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    Pub_Gpio_Output_AFPP(GPIOA, GPIO_Pin_2);
    Pub_Gpio_Input_INFLOATING(GPIOA, GPIO_Pin_3);
    Pub_Uart_Hardware_Cfg(USART2,DEBUG_UARTx_BAUD);
    Pub_Nvic_Config(USART2_IRQn, 0, 0);
    Pub_Uart_Int_Cfg(USART2);
}

/*-----------------------------------------------------------
** ��������: ����2��ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
static void Usart3_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    Pub_Gpio_Output_AFPP(GPIOB, GPIO_Pin_10);
    Pub_Gpio_Input_INFLOATING(GPIOB, GPIO_Pin_11);
    Pub_Uart_Hardware_Cfg(USART3,DEBUG_UARTx_BAUD);
    Pub_Nvic_Config(USART3_IRQn, 0, 0);
    Pub_Uart_Int_Cfg(USART3);
}

/*-----------------------------------------------------------
** ��������: �����ж���ں���
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
void DEBUG_UARTx_IRQ(void)
{
    if(USART_GetITStatus(DEBUG_UARTx, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(DEBUG_UARTx,USART_IT_RXNE);
        USART_Recv_Handle(Sys.Comm[0]);
    }
}

/*-----------------------------------------------------------
** ��������: ���ڷ�����������
** ��ڲ���: buf�������׵�ַ
             len�����鳤��
** ���ڲ���: ��
-------------------------------------------------------------*/
void Usart_SendBuf(u8 *buf,vu16 len)
{
	vu16 t;
	for(t=0; t<len; t++)                       
	{
		  while ((DEBUG_UARTx->SR&0X40) == 0);        
		  DEBUG_UARTx->DR = buf[t];
	}    
	while((DEBUG_UARTx->SR&0X40)==0);
}

/*-----------------------------------------------------------
** ��������: ���ڽ������ݺ���
** ��ڲ���: ��
** ���ڲ���: DEBUG_UARTx->DR�����ڽ�������ֵ
-------------------------------------------------------------*/
uint16_t Usart_RecvData(void)
{
    return (uint16_t)(DEBUG_UARTx->DR & (uint16_t)0x01FF);
}

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_UARTx->SR&0X40)==0);//ѭ������,ֱ���������   
    DEBUG_UARTx->DR = (u8) ch;      
	return ch;
}
#endif


