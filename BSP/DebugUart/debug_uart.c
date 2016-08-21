#include "debug_uart.h"

static void Usart1_Init(void);
static void Usart2_Init(void);
static void Usart3_Init(void);

/*-----------------------------------------------------------
** 功能描述: 调试串口初始化
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void Debug_Uart_Init(void)
{
    USART_DeInit(DEBUG_UARTx);
    if(DEBUG_UARTx == USART1)       Usart1_Init();
    else if(DEBUG_UARTx == USART2)  Usart2_Init();
    else if(DEBUG_UARTx == USART3)  Usart3_Init();
}

/*-----------------------------------------------------------
** 功能描述: 串口1初始化
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 串口2初始化
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 串口2初始化
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 串口中断入口函数
** 入口参数: 无
** 出口参数: 无
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
** 功能描述: 串口发送数组数据
** 入口参数: buf：数组首地址
             len：数组长度
** 出口参数: 无
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
** 功能描述: 串口接收数据函数
** 入口参数: 无
** 出口参数: DEBUG_UARTx->DR：串口接收数据值
-------------------------------------------------------------*/
uint16_t Usart_RecvData(void)
{
    return (uint16_t)(DEBUG_UARTx->DR & (uint16_t)0x01FF);
}

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_UARTx->SR&0X40)==0);//循环发送,直到发送完毕   
    DEBUG_UARTx->DR = (u8) ch;      
	return ch;
}
#endif


