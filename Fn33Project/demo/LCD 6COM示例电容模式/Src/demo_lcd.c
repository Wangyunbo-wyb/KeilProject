#include "demo_lcd.h"

void LcdInit(void)
{
    FL_GPIO_InitTypeDef gpioInitStruction = {0};
    FL_LCD_InitTypeDef lcdInitStruction;

    // GPIO Init
    gpioInitStruction.mode = FL_GPIO_MODE_ANALOG;
    gpioInitStruction.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    gpioInitStruction.pull = FL_DISABLE;
    gpioInitStruction.analogSwitch = FL_DISABLE;

    gpioInitStruction.pin = FL_GPIO_PIN_0 | FL_GPIO_PIN_1 | FL_GPIO_PIN_2 |
                            FL_GPIO_PIN_3 | FL_GPIO_PIN_4 | FL_GPIO_PIN_5 | FL_GPIO_PIN_8 |
                            FL_GPIO_PIN_9 | FL_GPIO_PIN_10;
    FL_GPIO_Init(GPIOA, &gpioInitStruction);

    gpioInitStruction.pin = FL_GPIO_PIN_4 | FL_GPIO_PIN_5 | FL_GPIO_PIN_6 |
                            FL_GPIO_PIN_7 | FL_GPIO_PIN_8 | FL_GPIO_PIN_9 | FL_GPIO_PIN_10 |
                            FL_GPIO_PIN_11 | FL_GPIO_PIN_13 | FL_GPIO_PIN_14;
    FL_GPIO_Init(GPIOB, &gpioInitStruction);

    gpioInitStruction.pin = FL_GPIO_PIN_4 | FL_GPIO_PIN_5 | FL_GPIO_PIN_6 |
                            FL_GPIO_PIN_7 | FL_GPIO_PIN_8 | FL_GPIO_PIN_9 | FL_GPIO_PIN_10 |
                            FL_GPIO_PIN_11 | FL_GPIO_PIN_12;
    FL_GPIO_Init(GPIOC, &gpioInitStruction);

    gpioInitStruction.pin = FL_GPIO_PIN_0;
    FL_GPIO_Init(GPIOD, &gpioInitStruction);

    //电容模式引脚
    gpioInitStruction.mode = FL_GPIO_MODE_ANALOG;
    gpioInitStruction.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    gpioInitStruction.pull = FL_DISABLE;
    gpioInitStruction.analogSwitch = FL_ENABLE;

    gpioInitStruction.pin =  FL_GPIO_PIN_2 | FL_GPIO_PIN_3 | FL_GPIO_PIN_15; //VCIN1 VCIN2 VDISP0
    FL_GPIO_Init(GPIOB, &gpioInitStruction);

    gpioInitStruction.pin = FL_GPIO_PIN_0 | FL_GPIO_PIN_1;//VDISP2 VDISP3
    FL_GPIO_Init(GPIOC, &gpioInitStruction);

    gpioInitStruction.pin = FL_GPIO_PIN_12;//VDISP1
    FL_GPIO_Init(GPIOD, &gpioInitStruction);


    // LCD Init
    lcdInitStruction.biasCurrent = FL_LCD_BIAS_CURRENT_HIGH;
    lcdInitStruction.biasMode = FL_LCD_BIAS_MODE_4BIAS;
    lcdInitStruction.biasVoltage = FL_LCD_BIAS_VOLTAGE_LEVEL15;
    lcdInitStruction.COMxNum = FL_LCD_COM_NUM_6COM;
    lcdInitStruction.waveform = FL_LCD_WAVEFORM_TYPEA;
    lcdInitStruction.displayFreq = 64;
    lcdInitStruction.mode = FL_LCD_DRIVER_MODE_OUTER_CAPACITY;
    FL_LCD_Init(LCD, &lcdInitStruction);

    //电容驱动
    FL_LCD_SetCapDriverFreq(LCD, FL_LCD_CAP_DRIVER_FREQ_LSCLK_DIV128);//电容驱动频率
    FL_LCD_SetCapDriverMode(LCD, FL_LCD_CAP_DRIVER_MODE_ONE);//电容驱动方式

    // COM and SEG Init
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM0);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM1);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM2);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM3);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM4);
    FL_LCD_EnableCOMEN(LCD, FL_LCD_COMEN_COM5);

    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG0);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG1);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG2);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG3);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG4);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG5);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG6);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG7);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG8);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG9);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG10);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG11);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG12);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG13);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG14);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG15);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG16);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG17);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG18);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG19);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG20);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG21);
    FL_LCD_EnableSEGEN0(LCD, FL_LCD_SEGEN0_SEG22);

    FL_LCD_Enable(LCD);
}

void LcdDisplayAll(bool state)
{
    if(state == true)
    {
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG0, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG1, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG2, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG3, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG4, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG5, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG6, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG7, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG8, 0xffffffff);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG9, 0xffffffff);
    }

    else
    {
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG0, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG1, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG2, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG3, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG4, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG5, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG6, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG7, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG8, 0x00000000);
        FL_LCD_WriteData(LCD, FL_LCD_DATA_REG9, 0x00000000);
    }
}

uint32_t dispBuf[10] = {0};

void LcdDisplayRefresh(void)
{
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG0, dispBuf[0]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG1, dispBuf[1]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG2, dispBuf[2]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG3, dispBuf[3]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG4, dispBuf[4]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG5, dispBuf[5]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG6, dispBuf[6]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG7, dispBuf[7]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG8, dispBuf[8]);
    FL_LCD_WriteData(LCD, FL_LCD_DATA_REG9, dispBuf[9]);
}

// true: 点亮; false: 熄灭
void LcdDisplayBIT(uint32_t x, uint32_t y, bool value)
{
    FL_LCD_6COMDisplay(dispBuf, x - 1, y - 1, value);
    LcdDisplayRefresh();
}
