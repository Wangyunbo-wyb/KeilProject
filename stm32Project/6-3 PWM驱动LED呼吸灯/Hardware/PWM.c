#include "stm32f10x.h"                  // Device header

void PWM_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//重映射
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	//选择内部时钟
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	//向上计数
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	//CK_CNT_OV = CK_CNT / (ARR + 1)
	//				       = CK_PSC / (PSC + 1) / (ARR + 1)
	//周期，ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;
	//PSC预分屏器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;
	//重复计数器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	//配置时基单元
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_OCInitTypeDef TIM_OCInitStruct;
	//赋初始值
	//PWM频率：	Freq = CK_PSC / (PSC + 1) / (ARR + 1)
	//PWM占空比：	Duty = CCR / (ARR + 1)
	//PWM分辨率：	Reso = 1 / (ARR + 1)

	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;    //CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
	TIM_Cmd(TIM2,ENABLE);
	
}

void PWM_SetCompare1(uint16_t Compare){
	TIM_SetCompare1(TIM2,Compare);
	
	
}



