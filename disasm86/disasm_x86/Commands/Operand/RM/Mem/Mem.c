#include "Mem.h"

int Mem_ToStringBuf(char* buf, union MemValue val, MemType type, SIB sib, Mod rmMod, union ImmValue rmDisp, Prefix addrPrefix)
{
	RM_FullType rm_ftype = {(RM_Type)type, 0};
	if(rmMod != MOD_REG)
	{
		union RM_Value rm_val;
		
		if(type == MEM_TYPE32) rm_val.rm32 = val.mem32;
		else                   rm_val.rm16 = val.mem16;
		
		return RM_ToStringBuf(buf, rm_val, rm_ftype, sib, rmMod, rmDisp, addrPrefix);
	}
	
	return 0;
}

MemType Mem_SwitchMode16_32(int mode)
{
	return MEM_TYPE16 + mode;
}