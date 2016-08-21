#include "timer.h"

/*-----------------------------------------------------------
** 功能描述: 系统TICK定时器初始化
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void TIME_Tick_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx, ENABLE);        //定时器对应时钟初始化
    
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
	TIM_TimeBaseStructure.TIM_Period = 10000/TICK_PER_SECOND;   //自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;                 //预分频值  10Khz的计数频率
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TICK_TIMER, &TIM_TimeBaseStructure);       //初始化TIMx的时间基数单位
 
	TIM_ITConfig(TICK_TIMER,TIM_IT_Update ,ENABLE);             //使能定时器中断
    
    Pub_Nvic_Config(TICK_TIMER_IRQ, 1, 3);                      //设置定时器中断优先级

	TIM_Cmd(TICK_TIMER, ENABLE);                                //使能TIMx外设					 
}

/*-----------------------------------------------------------
** 功能描述: 系统TICK定时器中断入口
** 入口参数: 无
** 出口参数: 无
-------------------------------------------------------------*/
void TICK_TIMER_IRQHandler(void)
{
	if (TIM_GetITStatus(TICK_TIMER, TIM_IT_Update) != RESET)    //检查指定的TIM中断发生与否:TIM 中断源 
		{
            TIM_ClearITPendingBit(TICK_TIMER, TIM_IT_Update);   //清除TIMx的中断待处理位:TIM 中断源
            LBTIM_Tick();                                       //提供任务执行的时间片
		}
}
