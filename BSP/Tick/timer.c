#include "timer.h"

/*-----------------------------------------------------------
** ��������: ϵͳTICK��ʱ����ʼ��
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
void TIME_Tick_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx, ENABLE);        //��ʱ����Ӧʱ�ӳ�ʼ��
    
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
	TIM_TimeBaseStructure.TIM_Period = 10000/TICK_PER_SECOND;   //�Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;                 //Ԥ��Ƶֵ  10Khz�ļ���Ƶ��
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TICK_TIMER, &TIM_TimeBaseStructure);       //��ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TICK_TIMER,TIM_IT_Update ,ENABLE);             //ʹ�ܶ�ʱ���ж�
    
    Pub_Nvic_Config(TICK_TIMER_IRQ, 1, 3);                      //���ö�ʱ���ж����ȼ�

	TIM_Cmd(TICK_TIMER, ENABLE);                                //ʹ��TIMx����					 
}

/*-----------------------------------------------------------
** ��������: ϵͳTICK��ʱ���ж����
** ��ڲ���: ��
** ���ڲ���: ��
-------------------------------------------------------------*/
void TICK_TIMER_IRQHandler(void)
{
	if (TIM_GetITStatus(TICK_TIMER, TIM_IT_Update) != RESET)    //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
            TIM_ClearITPendingBit(TICK_TIMER, TIM_IT_Update);   //���TIMx���жϴ�����λ:TIM �ж�Դ
            LBTIM_Tick();                                       //�ṩ����ִ�е�ʱ��Ƭ
		}
}
