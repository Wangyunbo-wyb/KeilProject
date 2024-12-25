#include "main.h"
#include "pgl.h"

void PGLOperate()
{
    /*真值表配置*/
    FL_PGL_WriteLUTTruthTable(PGL, FL_PGL_LUT0, 0x7);
    /*LUT使能*/
    FL_PGL_EnableLUT(PGL, FL_PGL_LUT0);
}
