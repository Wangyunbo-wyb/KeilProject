#include "stm32f10x.h"
#include "delay.h"
#include "28byj_48.h"
//IN1-4 PB6-9 a-d
uint16_t zheng[4]={0x02000,0x0100,0x0080,0x0040};//ÄæÊ±Õë

void Motor_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
}

void Motor_corotation(uint8_t direction){
	int i=0;
	if(direction){
		for(i=3;i>=0;i--){
			GPIO_Write(GPIOB,zheng[i]);
			delay_ms(3);
		}
	}
	else{
		for(i=0;i<4;i++){
			GPIO_Write(GPIOB,zheng[i]);
			delay_ms(3);
		}
	}
}

void Motor_stop(){
	GPIO_Write(GPIOB,0x0000);
}

void Motor_Ctrl(uint16_t angle,uint8_t direction){
	uint16_t i=0;
	for(i=0;i<64*angle/45;i++){
		Motor_corotation(direction);
	}
	Motor_stop();
}
