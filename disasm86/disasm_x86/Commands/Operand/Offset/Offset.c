#include <stdio.h>
#include <inttypes.h>
#include "Offset.h"

int Offset_ToStringBuf(char* buf, union OffsetValue val, OffsetType type)
{
    switch(type)
    {
        case OFF8:  return sprintf(buf, "off 0x%" PRIX8,  val.off8);
        case OFF16: return sprintf(buf, "off 0x%" PRIX16, val.off16);
        case OFF32: return sprintf(buf, "off 0x%" PRIX32, val.off32);
		
		default: return 0;
    }
}

OffsetType Offset_SwitchMode16_32(int mode)
{
	return OFF16 + mode;
}

int Offset_GetVal(const uint8_t* opValPos, union OffsetValue* pval, OffsetType type)
{
	switch(type)
	{
		case OFF8:  pval->off8 = *opValPos;               return 1;
		case OFF16: pval->off16 = *((uint16_t*)opValPos); return 2;
		case OFF32: pval->off32 = *((uint32_t*)opValPos); return 4;
		
		default: return 0;
	}
}