#include "stm32f10x.h"                  // Device header

extern uint16_t Num;
void Timer_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//选择内部时钟
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	//向上计数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	//CK_CNT_OV = CK_CNT / (ARR + 1)
	//				       = CK_PSC / (PSC + 1) / (ARR + 1)
	//周期，ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;
	//PSC预分屏器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
	//重复计数器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	//配置时基单元
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//使能中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2,ENABLE);
}


void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
}
