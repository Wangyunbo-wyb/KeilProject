#include "demo_rtc.h"
#include <string.h>

// RTC中断处理函数
void RTC_IRQHandler(void)
{
uint32_t cdif_temp;     
    cdif_temp = CDIF->CR;                                         //将cdif 状态暂存  
    FL_CDIF_EnableVAOToCPU(CDIF);                                 //cpu与CDIF互通
    FL_CDIF_EnableCPUToVAO(CDIF);
    // 秒中断
    if(FL_ENABLE == FL_RTCB_IsEnabledIT_Second(RTCB) &&
            FL_SET == FL_RTCB_IsActiveFlag_Second(RTCB))          //查询标志是否置起
    {
        FL_RTCB_ClearFlag_Second(RTCB);                           //清除中断标志
    }

    // 分钟中断
    if(FL_ENABLE == FL_RTCB_IsEnabledIT_Minute(RTCB) &&
            FL_SET == FL_RTCB_IsActiveFlag_Minute(RTCB))          //查询标志是否置起
    {
        FL_RTCB_ClearFlag_Minute(RTCB);                           //清除中断标志
    }

    // 小时中断
    if(FL_ENABLE == FL_RTCB_IsEnabledIT_Hour(RTCB) &&
            FL_SET == FL_RTCB_IsActiveFlag_Hour(RTCB))            //查询标志是否置起
    {
        FL_RTCB_ClearFlag_Hour(RTCB);                             //清除中断标志
    }

    // 天中断
    if(FL_ENABLE == FL_RTCB_IsEnabledIT_Day(RTCB) &&
            FL_SET == FL_RTCB_IsActiveFlag_Day(RTCB))             //查询标志是否置起
    {
        FL_RTCB_ClearFlag_Day(RTCB);                              //清除中断标志
    }

    if(FL_ENABLE == FL_RTCB_IsEnabledIT_Stamp(RTCB) &&
            FL_SET == FL_RTCB_IsActiveFlag_Stamp(RTCB))           //查询时间戳中断标志是否置起
    {
        FL_RTCB_ClearFlag_Stamp(RTCB);                            //清除时间戳中断标志
    }

    CDIF->CR = cdif_temp;                                         //将cdif 状态恢复   
}

void RTCB_Init(void)
{
    FL_RTCB_InitTypeDef    RTCB_InitStruct;
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    RTCB_InitStruct.year = 0x21;
    RTCB_InitStruct.month = 0x1;
    RTCB_InitStruct.day = 0x1;
    RTCB_InitStruct.week = 0x1;
    RTCB_InitStruct.hour = 0x0;
    RTCB_InitStruct.minute = 0x0;
    RTCB_InitStruct.second = 0x0;

    FL_RTCB_Init(RTCB, &RTCB_InitStruct);


    FL_CDIF_EnableVAOToCPU(CDIF);                                 //cpu与CDIF互通
    FL_CDIF_EnableCPUToVAO(CDIF);

    FL_RTCB_ClearFlag_Second(RTCB);
    FL_RTCB_EnableIT_Second(RTCB);

    InterruptConfigStruct.preemptPriority = 0x00;
    FL_NVIC_Init(&InterruptConfigStruct, RTCx_IRQn);

}

//RTCB 秒时标输出， 秒时标从PH15引脚输出
void RTCB_TimeMarkOut(void)
{
    FL_CDIF_EnableVAOToCPU(CDIF);                                 //cpu与CDIF互通
    FL_CDIF_EnableCPUToVAO(CDIF);

    FL_RTCB_Enable(RTCB);     //RTCB使能

    FL_RTCB_SetTimeMarkOutput(RTCB, FL_RTCB_TIME_MARK_SEC);

    //PH15 在VAO域 所以初始化需要单独做
    FL_VAO_GPIO_DisablePH15Input(VAO);                            //不输入使能
    FL_VAO_GPIO_DisablePH15Pullup(VAO);                           //不上拉
    FL_VAO_GPIO_DisablePH15OpenDrain(VAO);                        //不开漏
    FL_VAO_GPIO_SetPH15Mode(VAO, FL_VAO_PH15_MODE_RTCOUT);        //RTCOUT

    FL_CDIF_DisableCPUToVAO(CDIF);                                //关闭cpu通向voa的通道 节省功耗
}

//获取RTCB模块的时间到 ram
uint8_t RTCB_GetRTCB(FL_RTCB_InitTypeDef *InitStructer)
{
    uint8_t n, i;
    uint8_t Result = 1;

    FL_RTCB_InitTypeDef TempTime1, TempTime2;

    for(n = 0 ; n < 3; n++)
    {
        FL_RTCB_GetTime(RTCB, &TempTime1);                  //读一次时间
        FL_RTCB_GetTime(RTCB, &TempTime2);                  //再读一次时间

        for(i = 0; i < 7; i++)                              //两者一致, 表示读取成功
        {
            if(((uint32_t *)(&TempTime1))[i] != ((uint32_t *)(&TempTime2))[i]) { break; }
        }

        if(i == 7)
        {
            Result = 0;
            memcpy((uint32_t *)(InitStructer), (uint32_t *)(&TempTime1), 7 * sizeof(uint32_t)); //读取正确则更新新的时间
            break;
        }
    }

    return Result;
}

//设置ram的时间到RTCB模块
uint8_t RTCB_SetRTCB(FL_RTCB_InitTypeDef *InitStructer)
{
    uint8_t n, i;
    uint8_t Result;
    FL_RTCB_InitTypeDef TempTime1;

    for(n = 0 ; n < 3; n++)
    {
        FL_RTCB_ConfigTime(RTCB, InitStructer);
        Result = RTCB_GetRTCB(&TempTime1);                  //读取确认设置结果

        if(Result == 0)
        {
            Result = 1;

            for(i = 0; i < 7; i++)                          //两者一致, 表示设置成功
            {
                if(((uint32_t *)(&TempTime1))[i] != ((uint32_t *)(InitStructer))[i])
                { break; }
            }

            if(i == 7)
            {
                Result = 0;
                break;
            }
        }
    }

    return Result;
}

//读写时间测试
void RTCB_ReadWrite(void)
{
    FL_RTCB_InitTypeDef   InitTime;
    FL_RTCB_InitTypeDef   GetTime;

    FL_CDIF_EnableVAOToCPU(CDIF);                                 //cpu与CDIF互通
    FL_CDIF_EnableCPUToVAO(CDIF);

    //在ram中设置写入的时间
    InitTime.year   = 0x20;
    InitTime.month  = 0x10;
    InitTime.day    = 0x02;
    InitTime.week   = 0x04;                                       //没有周寄存器，这个寄存器无效
    InitTime.hour   = 0x15;
    InitTime.minute = 0x00;
    InitTime.second = 0x00;

    RTCB_SetRTCB(&InitTime);                                      //将ram的时间 写入RTCB模块
    FL_DelayMs(1000);                                             //延时，不是必须。可以删掉。这里为了看RTCB在走时 ，所以等了1秒
    RTCB_GetRTCB(&GetTime);                                       //将RTCB模块的时间 读出到ram

    FL_CDIF_DisableCPUToVAO(CDIF);                                //关闭cpu通向voa的通道 节省功耗
}

//RTCB 时间戳
void RTCB_Stamp(void)
{
    FL_RTCB_InitTypeDef      TempTime;

    FL_CDIF_EnableVAOToCPU(CDIF);                                 //cpu与CDIF互通
    FL_CDIF_EnableCPUToVAO(CDIF);

    TempTime.year   = 0x20;
    TempTime.month  = 0x02;
    TempTime.day    = 0x21;
    TempTime.week   = 0x04;
    TempTime.hour   = 0x09;
    TempTime.minute = 0x00;
    TempTime.second = 0x00;
    FL_RTCB_Init(RTCB, &TempTime);

    FL_RTCB_Enable(RTCB);                                         //RTCB使能

    //PH15 在VAO域 所以初始化需要单独做
    FL_VAO_GPIO_SetPH15Mode(VAO, FL_VAO_PH15_MODE_INPUT);         //输入
    FL_VAO_GPIO_EnablePH15Input(VAO);                             //输入使能
    FL_VAO_GPIO_DisablePH15Pullup(VAO);                           //不上拉
    FL_VAO_GPIO_DisablePH15OpenDrain(VAO);                        //不开漏


    //时间戳寄存器配置
    FL_RTCB_EnableTamperPinDigitalFilter(RTCB);                   //滤波
    FL_RTCB_SetTimeStampEdge(RTCB, FL_RTCB_TIMESTAMP_EDGE_RISING);//上升沿

    FL_RTCB_ClearFlag_Stamp(RTCB);                                //清除时间戳中断标志
    FL_RTCB_EnableIT_Stamp(RTCB);                                 //中断允许

    NVIC_DisableIRQ(RTCx_IRQn);                                   //NVIC中断控制器配置
    NVIC_SetPriority(RTCx_IRQn, 2);
    NVIC_EnableIRQ(RTCx_IRQn);                                    //内核中断允许

    FL_RTCB_EnableTimestamp(RTCB);                                //使能时间戳

    FL_CDIF_DisableCPUToVAO(CDIF);                                //关闭cpu通向voa的通道 节省功耗
}

//RTCB 清备份寄存器
void RTCB_Clear_Buckup_REG(void)
{

    FL_CDIF_EnableVAOToCPU(CDIF);                                 //cpu与CDIF互通
    FL_CDIF_EnableCPUToVAO(CDIF);

    RTCB->BKR0 = 0x00;
    RTCB->BKR1 = 0x00;
    RTCB->BKR2 = 0x00;
    RTCB->BKR3 = 0x00;
    RTCB->BKR4 = 0x00;

    FL_CDIF_DisableCPUToVAO(CDIF);                                 //关闭cpu通向voa的通道 节省功耗
}


