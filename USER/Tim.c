
#include "Tim.h"



/*
 * ��������TIM3_Init()
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void TIM3_Init(void)
{
   
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	 
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		 
	TIM_TimeBaseStructure.TIM_Period = Period - 1;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;	    //
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
   TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //���Ϊ�ж�Դ
   TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR

  /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
}



