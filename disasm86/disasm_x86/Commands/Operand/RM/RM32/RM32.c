#include <string.h>
#include "../../MemOff/MemOff.h"
#include "RM32.h"

static int RM32_ToStringBuf_NoOff(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp);
static int RM32_ToStringBuf_Off8(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp);
static int RM32_ToStringBuf_Off32(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp);

int RM32_ToStringBuf(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp, Prefix addrPrefix)
{
	int res = 0;
    if(mod != MOD_REG)
	{
		res = Prefix_ToStringBuf(buf, addrPrefix);
		buf += res;
	}
	
	switch(mod)
	{
		case MOD_NO_OFFSET:    return res + RM32_ToStringBuf_NoOff(buf, val, mod, regType, sib, rmDisp);
		case MOD_OFFSET_8:     return res + RM32_ToStringBuf_Off8(buf, val, mod, regType, sib, rmDisp);
		case MOD_OFFSET_16_32: return res + RM32_ToStringBuf_Off32(buf, val, mod, regType, sib, rmDisp);
		case MOD_REG:          return Reg_ToStringBuf(buf, val.rm32_mod11, regType);
		
		default: return res;
	}
}

static int RM32_ToStringBuf_NoOff(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp)
{
	switch(val.rm32_mod00)
	{
		case ADDR_EAX:    strcpy(buf, "[eax]"); return 5;
		case ADDR_ECX:    strcpy(buf, "[ecx]"); return 5;
		case ADDR_EDX:    strcpy(buf, "[edx]"); return 5;
		case ADDR_EBX:    strcpy(buf, "[ebx]"); return 5;
		case ADDR_SIB:    return SIB_ToStringBuf(buf, sib, mod, rmDisp);
		case ADDR_DISP32: return MemOff_ToStringBuf(buf, (union MemOffValue)rmDisp.imm32, MOFF32, PREFIX_NONE);
		case ADDR_ESI:    strcpy(buf, "[esi]"); return 5;
		case ADDR_EDI:    strcpy(buf, "[edi]"); return 5;
	}
}

static int RM32_ToStringBuf_Off8(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp)
{
	char* startBuf = buf;
	
	switch(val.rm32_mod01)
	{
		case ADDR_EAX_DISP8: strcpy(buf, "[eax+"); break;
		case ADDR_ECX_DISP8: strcpy(buf, "[ecx+"); break;
		case ADDR_EDX_DISP8: strcpy(buf, "[edx+"); break;
		case ADDR_EBX_DISP8: strcpy(buf, "[ebx+"); break;
		case ADDR_SIB_DISP8: return SIB_ToStringBuf(buf, sib, mod, rmDisp);
		case ADDR_EBP_DISP8: strcpy(buf, "[ebp+"); break;
		case ADDR_ESI_DISP8: strcpy(buf, "[esi+"); break;
		case ADDR_EDI_DISP8: strcpy(buf, "[edi+"); break;
			
		default: return 0;
	}
	buf += 5;
	buf += Imm_ToStringBuf(buf, rmDisp, IMM8);
	strcpy(buf, "]");
	buf++;
	
	return buf - startBuf;
}

static int RM32_ToStringBuf_Off32(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp)
{
	char* startBuf = buf;
	
	switch(val.rm32_mod10)
	{
		case ADDR_EAX_DISP32: strcpy(buf, "[eax+"); break;
		case ADDR_ECX_DISP32: strcpy(buf, "[ecx+"); break;
		case ADDR_EDX_DISP32: strcpy(buf, "[edx+"); break;
		case ADDR_EBX_DISP32: strcpy(buf, "[ebx+"); break;
		case ADDR_SIB_DISP32: return SIB_ToStringBuf(buf, sib, mod, rmDisp);
		case ADDR_EBP_DISP32: strcpy(buf, "[ebp+"); break;
		case ADDR_ESI_DISP32: strcpy(buf, "[esi+"); break;
		case ADDR_EDI_DISP32: strcpy(buf, "[edi+"); break;
			
		default: return 0;
	}
	buf += 5;
	buf += Imm_ToStringBuf(buf, rmDisp, IMM32);
	strcpy(buf, "]");
	buf++;
	
	return buf - startBuf;
}