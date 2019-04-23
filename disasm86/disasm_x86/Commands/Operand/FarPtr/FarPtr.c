#include <stdio.h>
#include <inttypes.h>
#include "FarPtr.h"

int FarPtr_ToStringBuf(char* buf, union FarPtrValue val, FarPtrType type)
{
    switch(type)
    {
        case FARPTR_16_16: return sprintf(buf, "0x%" PRIX16 ":0x%" PRIX16, val.farptr16_16.seg, val.farptr16_16.off);
        case FARPTR_16_32: return sprintf(buf, "0x%" PRIX16 ":0x%" PRIX32, val.farptr16_32.seg, val.farptr16_32.off);

        default: return 0;
    }
}

FarPtrType FarPtr_SwitchMode16_32(int mode)
{
	return FARPTR_16_16 + mode;
}

int FarPtr_GetVal(const uint8_t* opValPos, union FarPtrValue* pval, FarPtrType type)
{
	switch(type)
	{
		case FARPTR_16_16:
			pval->farptr16_16.seg = *((uint16_t*)opValPos);
			pval->farptr16_16.off = *((uint16_t*)(opValPos+2));
			return 4;
			
		case FARPTR_16_32:
			pval->farptr16_32.seg = *((uint16_t*)opValPos);
			pval->farptr16_32.off = *((uint32_t*)(opValPos+2));
			return 6;
			
		default: return 0;
	}
}