#include "rchftrim.h"
#include "fm33lg0xx_fl.h"

static void Soft_DelayUs(uint16_t us)
{
    uint32_t count;

    switch(FL_CMU_RCHF_GetFrequency())
    {
        case FL_CMU_RCHF_FREQUENCY_8MHZ:
            count = us * 1;
            break;
        case FL_CMU_RCHF_FREQUENCY_16MHZ:
            count = us * 2;
            break;
        case FL_CMU_RCHF_FREQUENCY_24MHZ:
            count = us * 3;
            break;
        case FL_CMU_RCHF_FREQUENCY_32MHZ:
            count = us * 4;
            break;
        default:
            count = us * 1;
            break;
    }

    while(count--)
    {
        __NOP();
        __NOP();
        __NOP();
        __NOP();
    }
}

static int32_t CCLCapture(int32_t timeout)
{
    uint32_t capture;

    FL_CMU_ClearFlag_CCLComplete();
    FL_CMU_CCL_Enable();  //启动校准

    while((timeout--) > 0)
    {
        Soft_DelayUs(10);   // 软件延时: >10us查询一个标志
        if(FL_SET == FL_CMU_IsActiveFlag_CCLComplete())
        {
            FL_CMU_ClearFlag_CCLComplete();
            break;
        }
    }

    capture = FL_CMU_CCL_ReadCounter();

    FL_CMU_CCL_Disable();  //校准电路复位

    if(timeout <= 0)
    {
        return -1;
    }

    return capture;
}

// Trim参数信息(推算RCHF Trim值)
// 理论捕捉值：(1 / (基准时钟 / 时钟分频)) / (1 / 调校时钟) = 目标计数值
// 每Trim对应捕捉值：目标计数值 * 调校步长(%) = 计数值步长
// 保证Trim频率精度：目标计数值 * 误差范围(%) = 计数值范围
uint32_t trimTarget = 0;
uint32_t trimError = 0;
float trimStep = 0;

int32_t RchfTrimInit(void)
{
    // 时钟选择
    FL_CMU_CCL_SetCalibrationClockSource(FL_CMU_CCL_CALCLK_SOURCE_RCHF);  //校准时钟选择
    FL_CMU_CCL_SetReferenceClockSource(FL_CMU_CCL_REFCLK_SOURCE_XTLF);    //参考时钟选择

    // 时钟分频
    FL_CMU_CCL_SetReferenceClockPrescaler(FL_CMU_CCL_REFCLK_PSC_DIV64);   //参考时钟64分频
    switch(FL_CMU_RCHF_GetFrequency())
    {
        case FL_CMU_RCHF_FREQUENCY_8MHZ:    // 不分频
            FL_CMU_CCL_SetCalibrationClockPrescaler(FL_CMU_CCL_CALCLK_PSC_DIV1);  //校准时钟分频
            trimTarget = 15625; // (1 / (32768 / 64)) / (1 / (8000000 / 1))
            trimError = 31;     // 15625 * 0.2%
            trimStep = 39.0625; // 15625 * 0.25%
            break;

        case FL_CMU_RCHF_FREQUENCY_16MHZ:   // 2分频
            FL_CMU_CCL_SetCalibrationClockPrescaler(FL_CMU_CCL_CALCLK_PSC_DIV2);
            trimTarget = 15625; // (1 / (32768 / 64)) / (1 / (16000000 / 2))
            trimError = 31;     // 15625 * 0.2%
            trimStep = 39.0625; // 15625 * 0.25%
            break;

        case FL_CMU_RCHF_FREQUENCY_24MHZ:   // 4分频
            FL_CMU_CCL_SetCalibrationClockPrescaler(FL_CMU_CCL_CALCLK_PSC_DIV4);
            trimTarget = 11719; // (1 / (32768 / 64)) / (1 / (24000000 / 4))
            trimError = 23;     // 11719 * 0.2%
            trimStep = 29.30;   // 11719 * 0.25%
            break;

        case FL_CMU_RCHF_FREQUENCY_32MHZ:   // 4分频
            FL_CMU_CCL_SetCalibrationClockPrescaler(FL_CMU_CCL_CALCLK_PSC_DIV4);
            trimTarget = 15625; // (1 / (32768 / 64)) / (1 / (32000000 / 4))
            trimError = 31;     // 15625 * 0.2%
            trimStep = 39.0625; // 15625 * 0.25%
            break;

        default:
            return -0x01;
    }

    // 清除基准时钟停振标志
    FL_CDIF_EnableCPUToVAO(CDIF);
    FL_VAO_ClearFlag_XTLFFail(VAO);

    return 0;
}

int32_t RchfTrimDeInit(void)
{
    return 0;
}

int32_t RchfTrimCalculte(uint8_t *trim)
{
    int32_t captureTemp;
    uint8_t tempbyte, rchfTrim;

    if(FL_VAO_IsActiveFlag_XTLFFail(VAO) == FL_SET)
    {
        FL_VAO_ClearFlag_XTLFFail(VAO);
        return -0x11;
    }

    captureTemp = CCLCapture(1000);

    if(FL_VAO_IsActiveFlag_XTLFFail(VAO) == FL_SET)
    {
        FL_VAO_ClearFlag_XTLFFail(VAO);
        return -0x12;
    }

    if(captureTemp < 0)
    {
        return -0x13;
    }

    if((captureTemp > (trimTarget - trimError)) &&
            (captureTemp < (trimTarget + trimError)))
    {
        *trim = FL_CMU_RCHF_ReadTrimValue();
    }
    else
    {
        rchfTrim = FL_CMU_RCHF_ReadTrimValue(); //读取RCHF校准值

        if(captureTemp > trimTarget)
        {
            captureTemp = captureTemp - trimTarget;
            tempbyte = (uint8_t)(captureTemp / trimStep + 0.5);

            if(rchfTrim >= tempbyte)
            {
                *trim = rchfTrim - tempbyte;
            }
            else
            {
                *trim = 0x00;
            }
        }
        else
        {
            captureTemp = trimTarget - captureTemp;
            tempbyte = (uint8_t)(captureTemp / trimStep + 0.5);

            if((rchfTrim + tempbyte) <= 0xff)
            {
                *trim = rchfTrim + tempbyte;
            }
            else
            {
                *trim = 0xff;
            }
        }
    }

    return 0;
}

int32_t RchfTrim(uint8_t *trim, uint16_t count)
{
    int32_t state = 0;

    state = RchfTrimInit();
    if(state == 0)
    {
        while(count--)
        {
            state = RchfTrimCalculte(trim++);     //获取count次捕捉值
            if(state != 0)
            {
                break;
            }
        }
    }

    RchfTrimDeInit();

    return state;
}

bool RchfTrimCheck(uint8_t *trim, uint16_t count, uint8_t limit)      //选择排序，
{
    uint8_t temp;
    uint16_t i, j;

    for(i = 0; i < count; i++)
    {
        for(j = i; j < count; j++)
        {
            if(trim[j] < trim[i])
            {
                temp = trim[j];
                trim[j] = trim[i];
                trim[i] = temp;
            }
        }
    }

    if((trim[count - 1] - trim[0]) > limit)       //最大trim差值不能超过limit
    {
        return false;
    }

    return true;
}

bool RchfTrimCheckN(uint8_t *trim, uint16_t count)
{
    // TODO: Other Checks Method.
    return false;
}

void RchfFoutOutput(void)
{
    FL_GPIO_InitTypeDef gpioInitStruct = {0};

    gpioInitStruct.pin             = FL_GPIO_PIN_11;
    gpioInitStruct.mode            = FL_GPIO_MODE_DIGITAL;
    gpioInitStruct.outputType      = FL_GPIO_OUTPUT_PUSHPULL;
    gpioInitStruct.pull            = FL_DISABLE;
    gpioInitStruct.remapPin        = FL_DISABLE;
    gpioInitStruct.analogSwitch    = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &gpioInitStruct);

    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_RCHF_DIV64);
}
