#include "demo_rtc.h"
#include <string.h>

// RTC中断处理函数
void RTC_IRQHandler(void)
{

    if(FL_ENABLE == FL_RTCA_IsEnabledIT_Alarm(RTCA) &&              //闹钟中断
            FL_SET == FL_RTCA_IsActiveFlag_Alarm(RTCA))             //查询标志是否置起
    {
        FL_RTCA_ClearFlag_Alarm(RTCA);                              //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_1KHz(RTCA) &&               //1KHz中断
            FL_SET == FL_RTCA_IsActiveFlag_1KHz(RTCA))              //查询标志是否置起
    {
        FL_RTCA_ClearFlag_1KHz(RTCA);                               //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_256Hz(RTCA) &&              //256Hz中断
            FL_SET == FL_RTCA_IsActiveFlag_256Hz(RTCA))             //查询标志是否置起
    {
        FL_RTCA_ClearFlag_256Hz(RTCA);                              //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_64Hz(RTCA) &&               //64Hz中断
            FL_SET == FL_RTCA_IsActiveFlag_64Hz(RTCA))              //查询标志是否置起
    {
        FL_RTCA_ClearFlag_64Hz(RTCA);                               //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_16Hz(RTCA) &&               //16Hz中断
            FL_SET == FL_RTCA_IsActiveFlag_16Hz(RTCA))              //查询标志是否置起
    {
        FL_RTCA_ClearFlag_16Hz(RTCA);                               //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_8Hz(RTCA) &&                //8Hz中断
            FL_SET == FL_RTCA_IsActiveFlag_8Hz(RTCA))               //查询标志是否置起
    {
        FL_RTCA_ClearFlag_8Hz(RTCA);                                //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_4Hz(RTCA) &&                //4Hz中断
            FL_SET == FL_RTCA_IsActiveFlag_4Hz(RTCA))               //查询标志是否置起
    {
        FL_RTCA_ClearFlag_4Hz(RTCA);                                //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_2Hz(RTCA) &&                //2Hz中断
            FL_SET == FL_RTCA_IsActiveFlag_2Hz(RTCA))               //查询标志是否置起
    {
        FL_RTCA_ClearFlag_2Hz(RTCA);                                //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_Second(RTCA) &&             //秒中断
            FL_SET == FL_RTCA_IsActiveFlag_Second(RTCA))            //查询标志是否置起
    {
        FL_RTCA_ClearFlag_Second(RTCA);                             //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_Minute(RTCA) &&             //分钟中断
            FL_SET == FL_RTCA_IsActiveFlag_Minute(RTCA))            //查询标志是否置起
    {
        FL_RTCA_ClearFlag_Minute(RTCA);                             //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_Hour(RTCA) &&               //小时中断
            FL_SET == FL_RTCA_IsActiveFlag_Hour(RTCA))              //查询标志是否置起
    {
        FL_RTCA_ClearFlag_Hour(RTCA);                               //清除中断标志
    }


    if(FL_ENABLE == FL_RTCA_IsEnabledIT_Day(RTCA) &&                //天中断
            FL_SET == FL_RTCA_IsActiveFlag_Day(RTCA))               //查询标志是否置起
    {
        FL_RTCA_ClearFlag_Day(RTCA);                                //清除中断标志
    }
}

void RTCA_Init(void)
{
    FL_RTCA_InitTypeDef    RTCA_InitStruct;
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    RTCA_InitStruct.year = 0x21;
    RTCA_InitStruct.month = 0x1;
    RTCA_InitStruct.day = 0x1;
    RTCA_InitStruct.week = 0x0;
    RTCA_InitStruct.hour = 0x0;
    RTCA_InitStruct.minute = 0x0;
    RTCA_InitStruct.second = 0x0;

    FL_RTCA_Init(RTCA, &RTCA_InitStruct);                                                 /*RTCA初始化*/

    FL_RTCA_ClearFlag_Second(RTCA);
    FL_RTCA_EnableIT_Second(RTCA);

    InterruptConfigStruct.preemptPriority = 0x02;
    FL_NVIC_Init(&InterruptConfigStruct, RTCx_IRQn);
}


//RTCA 闹钟中断设置
void RTCA_AlarmTimeSet(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;
    //设置闹钟时间
    FL_RTCA_WriteHourAlarm(RTCA, 0x00);                             //时
    FL_RTCA_WriteMinuteAlarm(RTCA, 0x00);                           //分
    FL_RTCA_WriteSecondAlarm(RTCA, 0x10);                           //秒

    FL_RTCA_ClearFlag_Alarm(RTCA);                                  //清除闹钟中断标志
    FL_RTCA_EnableIT_Alarm(RTCA);                                   //打开闹钟中断

    InterruptConfigStruct.preemptPriority = 0x02;                                         /*配置RTCA_NVIC*/
    FL_NVIC_Init(&InterruptConfigStruct, RTCx_IRQn);
}

//RTCA 秒时标输出， 秒时标从PD11引脚输出
void RTCA_TimeMarkOut(void)
{
    FL_RTCA_Enable(RTCA);
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};


    FL_RTCA_SetTimeMarkOutput(RTCA, FL_RTCA_TIME_MARK_SEC);         //RTCA秒时标选择

    //PD11引脚,配置成fout0功能
    GPIO_InitStruct.pin = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);


    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_RTCTM);             //FOUT0输出选择RTCA时标
}

//获取RTCA模块的时间到 ram
uint8_t RTCA_GetRTCA(FL_RTCA_InitTypeDef *InitStructer)
{
    uint8_t n, i;
    uint8_t Result = 1;

    FL_RTCA_InitTypeDef TempTime1, TempTime2;

    for(n = 0 ; n < 3; n++)
    {
        FL_RTCA_GetTime(RTCA, &TempTime1); //读一次时间
        FL_RTCA_GetTime(RTCA, &TempTime2); //再读一次时间

        for(i = 0; i < 7; i++) //两者一致, 表示读取成功
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

//设置ram的时间到RTCA模块
uint8_t RTCA_SetRTCA(FL_RTCA_InitTypeDef *InitStructer)
{
    uint8_t n, i;
    uint8_t Result;
    FL_RTCA_InitTypeDef TempTime1;

    for(n = 0 ; n < 3; n++)
    {
        FL_RTCA_ConfigTime(RTCA, InitStructer);
        Result = RTCA_GetRTCA(&TempTime1);    //读取确认设置结果

        if(Result == 0)
        {
            Result = 1;

            for(i = 0; i < 7; i++) //两者一致, 表示设置成功
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

//读写时间
void RTCA_ReadWrite(void)
{
    FL_RTCA_InitTypeDef   InitTime;
    FL_RTCA_InitTypeDef   GetTime;

    FL_RTCA_Enable(RTCA);
    //在ram中设置写入的时间
    InitTime.year   = 0x20;
    InitTime.month  = 0x10;
    InitTime.day    = 0x02;
    InitTime.week   = 0x04;
    InitTime.hour   = 0x15;
    InitTime.minute = 0x00;
    InitTime.second = 0x00;

    //将ram的时间 写入RTCA模块
    RTCA_SetRTCA(&InitTime);

    FL_DelayMs(1000); //延时，不是必须。可以删掉。这里为了看RTCA在走时 ，所以等了1秒

    //将RTCA模块的时间 读出到ram
    RTCA_GetRTCA(&GetTime);
}


