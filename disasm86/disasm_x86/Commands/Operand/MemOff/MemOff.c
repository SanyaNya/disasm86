#include <stdio.h>
#include <inttypes.h>
#include "MemOff.h"

int MemOff_ToStringBuf(char* buf, union MemOffValue val, MemOffType type, Prefix addrPrefix)
{
	int res = 0;
	if(addrPrefix != PREFIX_NONE)
		res = Prefix_ToStringBuf(buf, addrPrefix);
	buf += res;
	
    switch(type)
    {
        case MOFF8:  return res + sprintf(buf, "[0x%" PRIX8 "]",  val.moff8);
        case MOFF16: return res + sprintf(buf, "[0x%" PRIX16 "]", val.moff16);
        case MOFF32: return res + sprintf(buf, "[0x%" PRIX32 "]", val.moff32);
		
        default: return res;
    }
}

MemOffType MemOff_SwitchMode16_32(int mode)
{
	return MOFF16 + mode;
}

int MemOff_GetVal(const uint8_t* opValPos, union MemOffValue* pval, MemOffType type)
{
	switch(type)
	{
		case MOFF8:  pval->moff8 = *opValPos;               return 1;
		case MOFF16: pval->moff16 = *((uint16_t*)opValPos); return 2;
		case MOFF32: pval->moff32 = *((uint32_t*)opValPos); return 4;
		
		default: return 0;
	}
}