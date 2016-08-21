#include "delay.h"

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数

/*-----------------------------------------------------------
** 功能描述: 延时程序初始化
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void Delay_Init(void)	 
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us = SystemCoreClock/8000000;                       //系统时钟的1/8
	fac_ms =(u16)fac_us*1000;                               //每个ms需要的systick时钟数   
}

/*-----------------------------------------------------------
** 功能描述: 微妙级延时
** 入口参数: nus:微妙数
** 出口参数: 无
-------------------------------------------------------------*/
void Delay_Us(vu32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD   = nus*fac_us;                   //时间加载	  		 
	SysTick->VAL    = 0x00;                         //清空计数器
	SysTick->CTRL   |= SysTick_CTRL_ENABLE_Msk ;    //开始倒数	 
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp&0x01 && !(temp&(1<<16)));            //等待时间到达   
	SysTick->CTRL   &= ~SysTick_CTRL_ENABLE_Msk;    //关闭计数器
	SysTick->VAL    = 0X00;                         //清空计数器	 
}

/*-----------------------------------------------------------
** 功能描述: 毫秒级延时
** 入口参数: nms:毫秒数
** 出口参数: 无
** Note: nms <= 0xffffff*8*1000/SYSTICK 即小于1864ms
-------------------------------------------------------------*/
void Delay_Ms(vu16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD   = (u32)nms*fac_ms;              //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL    = 0x00;                         //清空计数器
	SysTick->CTRL   |= SysTick_CTRL_ENABLE_Msk ;    //开始倒数  
	do
	{
		temp = SysTick->CTRL;
	}
	while(temp&0x01 && !(temp&(1<<16)));            //等待时间到达   
	SysTick->CTRL   &= ~SysTick_CTRL_ENABLE_Msk;    //关闭计数器
	SysTick->VAL    = 0X00;                         //清空计数器	  	    
} 

