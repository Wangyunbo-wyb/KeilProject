#include "stm32f10x.h"                  // Device header

#include "Delay.h"
#include "usart3.h"
#include "lora_app.h"
#include "string.h"
#include "stdio.h"
#include "Delay.h"
#include "usart1.h"
#include "28byj_48.h"
#include "OLED.h"
extern uint8_t dat[5];
extern u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 			//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
extern uint16_t len123;
extern vu16 USART3_RX_STA;
char str123[40];
uint8_t len_usart1=0;
int main(){
	char msg[40]="16hello\r\n";
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	
	Motor_Init();
	
	uart_init(115200);
	usart3_init(115200);
	LoRa_Init();
	while(1){
		if(str123[len_usart1]=='\0'&&len_usart1!=0){
			sprintf(msg,"%s",str123);
			len_usart1=0;
			LoRa_SendData((char*)msg);
		}
		OLED_ShowString(1,1,msg);//显示发送的数据	
		Motor_Ctrl(180,1);
		delay_ms(1000);
	}
}
