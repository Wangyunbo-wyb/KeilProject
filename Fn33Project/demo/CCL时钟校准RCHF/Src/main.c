#include "main.h"
#include "fm33lg0xx_fl.h"
#include "rchftrim.h"

uint8_t trim[7];
bool TrimState = true;
int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();

    // 通过FOUT0观测RCHF_64分频输出
    RchfFoutOutput();

    // 获取目标Trim值，并进行数据稳定性判断
    if(RchfTrim(trim, 7) == 0)
    {
        if(RchfTrimCheck(trim, 7, 3) == true)
        {
            if(trim[3] == 0x00 | trim[3] == 0xff)
            {
                TrimState = false;
            }
            else
            {
                FL_CMU_RCHF_WriteTrimValue(trim[3]);
            }
        }
    }

    // 需要重复该步骤，以确保校准精度
    if(RchfTrim(trim, 7) == 0)
    {
        if(RchfTrimCheck(trim, 7, 3) == true)
        {
            if(trim[3] == 0x00 | trim[3] == 0xff)
            {
                TrimState = false;
            }
            else
            {
                FL_CMU_RCHF_WriteTrimValue(trim[3]);
            }
        }
    }

    //// 针对32M,再次重复该步骤，以确保校准精度
    //      if (RchfTrim(trim, 7) == 0)
    //    {
    //        if (RchfTrimCheck(trim, 7, 3) == true)
    //        {
    //                    if(trim[3] == 0x00 | trim[3] == 0xff)
    //                      {
    //                         TrimState = false;
    //                      }
    //                      else
    //                      {
    //                         FL_CMU_RCHF_WriteTrimValue(trim[3]);
    //                      }
    //        }
    //    }


    while(1)
    {

    }
}


