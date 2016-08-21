#include "bsp.h"

/*******************************************************************************
* 
*                                   RCC����
* 
*******************************************************************************/
static void RCC_Configuration(void)
{   
	ErrorStatus HSEStartUpStatus;
    
	RCC_DeInit(); 							                //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ 
  	RCC_HSEConfig(RCC_HSE_ON);				                //���ⲿ���پ��� 
  	HSEStartUpStatus = RCC_WaitForHSEStartUp();             //�ȴ��ⲿ����ʱ��׼����
	//�ⲿ����ʱ���Ѿ�׼���
  	if(HSEStartUpStatus == SUCCESS)  
  	{
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
    	RCC_HCLKConfig(RCC_SYSCLK_Div1);	                //����AHB(HCLK)ʱ��=SYSCLK
    	RCC_PCLK2Config(RCC_HCLK_Div1); 	                //����APB2(PCLK2)��=AHBʱ��
    	RCC_PCLK1Config(RCC_HCLK_Div2); 	                //����APB1(PCLK1)��=AHB 1/2ʱ�� 	
    	RCC_ADCCLKConfig(RCC_PCLK2_Div4);	                //����ADCʱ��=PCLK2 1/4 
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//����PLLʱ�� == �ⲿ���پ���ʱ��*9
    	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	                //����ADCʱ��= PCLK2/6   //72M/6=12,ADC���ʱ�䲻�ܳ���14M
    	RCC_PLLCmd(ENABLE); 				                //ʹ��PLLʱ�� 
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //�ȴ�PLLʱ�Ӿ���
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);          //����ϵͳʱ�� = PLLʱ�� 
    	while(RCC_GetSYSCLKSource() != 0x08);               //���PLLʱ���Ƿ���Ϊϵͳʱ��
  	}
    
    RCC_ClocksTypeDef  RCC_Clocks;
    
	RCC_GetClocksFreq(&RCC_Clocks);
    
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                            RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF |
                            RCC_APB2Periph_GPIOG , ENABLE);
}

/*******************************************************************************
* 
*                                   NVIC����
* 
*******************************************************************************/
static void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(SYS_GROUP_PRIORITY); 
}


/*******************************************************************************
* 
*                                ϵͳӲ����ʼ��
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
