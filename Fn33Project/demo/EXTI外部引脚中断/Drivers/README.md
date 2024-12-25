- ## FM33LG0xx FL驱动库改版记录

  ### v2.0.0

  - 首次发布

  ### v2.0.1

  - **fm33lg0xx_fl.h**：FL_DELAY_US和FL_DELAY_MS使用SystemCoreClock实现，用户在修改主频后可以直接调用SystemCoreClockUpdate()函数让FL库延时保持准确。
  - **fm33lg0xx_fl_adc.h**：添加PTAT定标值。
  - **fm33lg0xx_fl_cmu.h**：修改CMU_XTHFCR_CFG位段Mask宽度错误，并相应修改FL库函数中的移位值。
  - **fm33lg0xx_fl_gpio.h**：修改了控制使能外部中断相关寄存器的FL库函数中的Mask宽度错误导致无法使能或禁止外部中断线16,17,18的问题。
  - **fm33lg0xx_fl_iwdt.h**：IWDT操作窗口的函数功能采用直接操作寄存器实现，加快操作速度。
  - **fm33lg0xx_fl_lcd.h**：修复注释乱码问题。
  - **fm33lg0xx_fl_uart.h，fm33lg0xx_fl_lpuart.h**：修改UART和LPUART的读写TXBUF/RXBUF以及LPUART的读写DMR的FL库函数的操作位宽为9位以支持9bit UART通讯。

  ### v2.1.0

  - **fm33lg0xx_fl_atim.c，fm33lg0xx_fl_atim.h**：ATIM输出比较初始化结构体FL_ATIM_OC_InitTypeDef中增加正向通道输出控制配置项。（该更新不向前兼容）

  ### v2.1.1

  - **CMSIS**：添加了fm33_assert.h头文件，解除FL驱动库和工程文件的耦合。
  - **fm33lg0xx_fl.h**：添加了对fm33_assert.h头文件的显式包含。
  - **fm33lg0xx_fl_lcd.h**：修正了FL_LCD_SEGEN0_SEG3宏定义的位宽错误。
  - **fm33lg0xx_fl_vrefp.h**：新增了对应的fm33lg0xx_fl_vrefp.c驱动文件，添加了FL_VREFP_Init初始化函数。
  - **fm33lg0xx_fl_adc.h**：修正了ADC初始化会导致在之前的FL_ADC_CommonInit配置被复位的问题。
  - **fm33lg0xx_fl_vao.h**：删除了多余头文件包含。

  ### v2.2.0

  - 文件变动：
    - 将**fm33_assert.h**文件从CMSIS对应目录移动到FL驱动库对应目录下；
    - 添加了**fm33lg0xx_fl_conf.h**和**fm33lg0xx_fl_def.h**，删除了**fm33xx.h**，将内容移动到**fm33lg0xx_fl_def.h**中；
    - 将**fm33lg0xx_fl.h**中的“包含外设头文件”部分的内容移动到了**fm33lg0xx_fl_conf.h**, 并在**fm33lg0xx_fl.h**中包含它。
    - 将**fm33lg0xx_fl.h**中的“FL驱动库返回类型定义”内容移动到了**fm33lg0xx_fl_def.h**, 并在**fm33lg0xx_fl.h**中包含它。
    - 将所有外设驱动.c文件的包含头文件替换为**fm33lg0xx_fl.h**，并使用FL_XXX_DRIVER_ENABLED条件编译包裹；
    - 将所有外设驱动.h文件的包含头文件替换为**fm33lg0xx_def.h**；
    - 取消使用#ifndef MFANG条件编译包裹外设的FL_XXX_DRIVER_ENABLED列表，防止冲突；

  - **CMSIS**：
    - **system_fm33lg0xx.c/.h**: 
      - 删除原先的XTHF_VALUE和XTLF_VALUE，取而代之定义了XTHFClock和XTLFClock全局变量。如果用户使用XTHF或者XTLF，需要在FL库初始化前为该两个变量重新赋予正确的值并调用SystemCoreClockUpdate()函数以正确初始化FL库延时函数；
      - 为SystemInit函数中的时钟配置部分使用#ifndef MFANG条件编译包裹起来，使得魔方能够掌控时钟初始化内容；
      - 添加**USE_IWDT_ON_STARTUP**和**IWDT_OVERFLOW_PERIOD**宏定义，如果配置为使能，则在SystemInit函数中就初始化IWDT，保证芯片初始化时的抗干扰能力；
      - 添加**USE_DEBUG_UNDER_SLEEP**宏定义，如果配置为使能，则启用在休眠下保持调试器连接；
      - 添加**USE_LSCLK_AUTO_SWITCH**宏定义用于在LSCLK使用XTLF（即打开**USE_LSCLK_CLOCK_SRC_XTLF**宏定义）时配置自动切换的使能。
    - **fm33lg0xx.h**：修改DMA通道存储地址寄存器名称为CHxMAD；
  - **fm33lg0xx_fl_cmu.c**，**fm33lg0xx_fl_uart.c**：修改获取时钟频率函数以适应CMSIS的修改；
  - **fm33lg0xx_fl_exti.c**：修改初始化函数，解决了选择的中断线大于等于16时产生的初始化不正确的问题。
  - **fm33lg0xx_fl_can.h**：修改函数FL_CAN_ClearFlag_CRXOK名称为FL_CAN_ClearFlag_RXOK；
  - **fm33lg0xx_fl_lpuart.h**：修改LPUART MCTL宏定义宽度为13bit；
  - **fm33lg0xx_fl_adc.c/.h**：合并初始化结构体**FL_ADC_CommonInitTypeDef**的时钟源配置，将**operationSource**项合并到**clockSource**，将**APBClockPrescaler**项合并到**clockPrescaler**。合并后，当前ADC可选时钟变为：
    - FL_CMU_ADC_CLK_SOURCE_RCLF
    - FL_CMU_ADC_CLK_SOURCE_RCHF
    - FL_CMU_ADC_CLK_SOURCE_XTHF
    - FL_CMU_ADC_CLK_SOURCE_PLL
    - FL_ADC_CLK_SOURCE_APBCLK
      ADC分频可选项变为：FL_ADC_CLK_PSC_DIV1/2/4/8/16/32，其中在时钟源为FL_ADC_CLK_SOURCE_APBCLK时，仅1,2,4,8分频可选。
  - **fm33lg0xx_fl_cmu.h**：修改**FL_CMU_LSCLK_SOURCE_XXX**宏定义为**FL_CMU_LSCLK_CLK_SOURCE_XXX**；修正**CMU_XTHFCR_CFG_Msk**位宽错误；
  - **fm33lg0xx_fl_comp.c/.h**：修改**FL_COMP_INP_SOURCE_ULPBG_AREF**宏定义为**FL_COMP_INP_SOURCE_ULPBG_REF**；
  - **fm33lg0xx_fl_atim.c, fm33lg0xx_fl_bstim16.c, fm33lg0xx_fl_bstim32.c, fm33lg0xx_fl_gptim.c**：修正外设初始化函数等待Update标志时错误地使用&判断的问题，改用&&。【重要】
  - **fm33lg0xx_fl_lcd.h**：修改**FL_LCD_SEGEN0_SEG3**位宽错误问题；

  - **fm33lg0xx_fl_lptim16.c/.h, fm33lg0xx_fl_lptim32.c/.h**：将**FL_LPTIM16/32_IC1_CAPTURE_SOURCE_XXX**修改为**FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP0 - FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP3**；

  ### v2.2.1

  - **system_fm33lg0xx.c**：修改默认PDR档位；
  - **fm33lg0xx_fl_gpio.h**：修改FL_GPIO_GetTriggerEdge1()函数移位错误；
  - **fm33lg0xx_fl_exti.c**：修改外部中断初始化延时顺序和延时值，保证顺利初始化；
  - **fm33lg0xx_fl_adc.c**：添加使能所有通道的宏定义；
