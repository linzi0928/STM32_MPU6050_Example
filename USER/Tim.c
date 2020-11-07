
#include "Tim.h"



/*
 * 函数名：TIM3_Init()
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
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
		 
	TIM_TimeBaseStructure.TIM_Period = Period - 1;       //当定时器从0计数到999，即为1000次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1;	    //
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
   TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //溢出为中断源
   TIM_ARRPreloadConfig(TIM3, ENABLE);			 // 使能TIM3重载寄存器ARR

  /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);                   //使能定时器3	
}




