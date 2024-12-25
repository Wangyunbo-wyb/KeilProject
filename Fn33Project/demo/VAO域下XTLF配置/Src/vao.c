#include "main.h"
#include "vao.h"

void FDET_IRQHandler(void)
{
   if(FL_VAO_IsActiveFlag_XTLFFail(VAO))
	 {
		 FL_CDIF_EnableCPUToVAO(CDIF);
		 FL_VAO_ClearFlag_XTLFFail(VAO);
     /*停振后客户处理逻辑*/
		 //...
	 }
}

void XTLFConfig(void)
{
    FL_VAO_XTLF_InitTypeDef  VAO_XTLF_InitStruct;
	  FL_NVIC_ConfigTypeDef    InterruptConfigStruct;
 
    /*跨电源域时序控制，相对于APBCLK的比例*/
    FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV2);

    /*使能CDIF*/
    FL_CDIF_EnableVAOToCPU(CDIF);
    FL_CDIF_EnableCPUToVAO(CDIF);

    /*XTLF电路在VAO域下，配置方法*/
    VAO_XTLF_InitStruct.driveMode                 = FL_VAO_XTLF_DRIVE_LEVEL_1;
    VAO_XTLF_InitStruct.workingCurrentMode        = FL_VAO_XTLF_WORK_CURRENT_450NA;
    (void)FL_VAO_XTLF_Init(VAO, &VAO_XTLF_InitStruct);

    FL_VAO_XTLF_Enable(VAO);        //上电后XTLF即默认开启
    FL_DelayMs(3000);               //XTLF上电使能，建立时间典型值1S，最大3S
		FL_VAO_ClearFlag_XTLFFail(VAO);
	
	
	  FL_VAO_EnableIT_XTLFFail(VAO);  //使能停振检测中断
		
    InterruptConfigStruct.preemptPriority = 0x00;
    FL_NVIC_Init(&InterruptConfigStruct, FDET_IRQn);  
}

