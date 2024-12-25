#include "main.h"

FL_ErrorStatus DIVAS_Init(void)
{
    return FL_DIVAS_Init(DIVAS);
}

FL_ErrorStatus DIVAS_Hdiv(void)
{
    int32_t DivisorEnd = 5;
    int16_t Divisor = 2;
    int32_t Quotient;
    int16_t Residue;
    uint32_t result = 0;
    DIVAS_Init();
    result = FL_DIVAS_Hdiv_Calculation(DIVAS, DivisorEnd, Divisor, &Quotient, &Residue);

    if(result == 0)
    {
        if((Quotient == (DivisorEnd / Divisor)) && (Residue == (DivisorEnd % Divisor)))
        { return FL_PASS; }
    }

    return FL_FAIL;
}


FL_ErrorStatus DIVAS_Root(void)
{
    uint32_t Root = 4;
    uint16_t Result=0;
    uint32_t status = 0;
    DIVAS_Init();
    status = FL_DIVAS_Root_Calculation(DIVAS, Root, &Result);

    if((status == 0) && (Result == 2))
    {
        return FL_PASS;
    }

    return FL_FAIL;
}

