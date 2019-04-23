#include "RM.h"

int RM_ToStringBuf(char* buf, union RM_Value val, RM_FullType ftype, SIB sib, Mod rmMod, union ImmValue rmDisp, Prefix addrPrefix)
{
	if(ftype.type == RM_TYPE32) return RM32_ToStringBuf(buf, val.rm32, rmMod, ftype.regType, sib, rmDisp, addrPrefix);
	else                        return RM16_ToStringBuf(buf, val.rm16, rmMod, ftype.regType, rmDisp, addrPrefix);
}

RM_Type RM_SwitchMode16_32(int mode)
{
	return RM_TYPE16 + mode;
}