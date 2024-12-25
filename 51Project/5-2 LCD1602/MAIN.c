#include <REGX52.H>
#include "LCD1602.h"
void main(){
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello");
	LCD_ShowNum(1,9,123,3);
	while(1){
		
	}
}
