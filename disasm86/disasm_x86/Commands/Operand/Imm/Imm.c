#include <stdio.h>
#include <inttypes.h>
#include "Imm.h"

int Imm_ToStringBuf(char* buf, union ImmValue val, ImmType type)
{
    switch(type)
    {
        case IMM8:  return sprintf(buf, "0x%" PRIX8,  val.imm8);
        case IMM16: return sprintf(buf, "0x%" PRIX16, val.imm16);
        case IMM32: return sprintf(buf, "0x%" PRIX32, val.imm32);

        default: return 0;
    }
}

ImmType Imm_SwitchMode16_32(int mode)
{
	return IMM16 + mode;
}

int Imm_GetVal(const uint8_t* opValPos, union ImmValue* pval, ImmType type)
{
	switch(type)
	{
		case IMM8:  pval->imm8  = *opValPos;              return 1;
		case IMM16: pval->imm16 = *((uint16_t*)opValPos); return 2;
		case IMM32: pval->imm32 = *((uint32_t*)opValPos); return 4;
		
		default: return 0;
	}
}