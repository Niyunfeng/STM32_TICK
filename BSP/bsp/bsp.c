#include "bsp.h"

/*******************************************************************************
* 
*                                   RCC配置
* 
*******************************************************************************/
static void RCC_Configuration(void)
{   
	ErrorStatus HSEStartUpStatus;
    
	RCC_DeInit(); 							                //复位RCC外部设备寄存器到默认值 
  	RCC_HSEConfig(RCC_HSE_ON);				                //打开外部高速晶振 
  	HSEStartUpStatus = RCC_WaitForHSEStartUp();             //等待外部高速时钟准备好
	//外部高速时钟已经准别好
  	if(HSEStartUpStatus == SUCCESS)  
  	{
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
    	RCC_HCLKConfig(RCC_SYSCLK_Div1);	                //配置AHB(HCLK)时钟=SYSCLK
    	RCC_PCLK2Config(RCC_HCLK_Div1); 	                //配置APB2(PCLK2)钟=AHB时钟
    	RCC_PCLK1Config(RCC_HCLK_Div2); 	                //配置APB1(PCLK1)钟=AHB 1/2时钟 	
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4);	                //配置ADC时钟=PCLK2 1/4 
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//配置PLL时钟 == 外部高速晶体时钟*9
    	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	                //配置ADC时钟= PCLK2/6   //72M/6=12,ADC最大时间不能超过14M
    	RCC_PLLCmd(ENABLE); 				                //使能PLL时钟 
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //等待PLL时钟就绪
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);          //配置系统时钟 = PLL时钟 
    	while(RCC_GetSYSCLKSource() != 0x08);               //检查PLL时钟是否作为系统时钟
  	}
    
    RCC_ClocksTypeDef  RCC_Clocks;
    
	RCC_GetClocksFreq(&RCC_Clocks);
    
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                            RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |
                            RCC_APB2Periph_GPIOG , ENABLE);
}

/*******************************************************************************
* 
*                                   NVIC配置
* 
*******************************************************************************/
static void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(SYS_GROUP_PRIORITY); 
}


/*******************************************************************************
* 
*                                系统硬件初始化
* 
*******************************************************************************/
void BSP_Init(void)
{
    RCC_Configuration();
    NVIC_Configuration();
    
    Delay_Init();
    Debug_Gpio_Init();
    Debug_Uart_Init();
    
    TIME_Tick_Init();
    LBTIM_Init();
    CommRec_Init();
}
