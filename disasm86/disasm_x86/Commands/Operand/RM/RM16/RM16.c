#include <string.h>
#include "../../MemOff/MemOff.h"
#include "RM16.h"

static int RM16_ToStringBuf_NoOff(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp);
static int RM16_ToStringBuf_Off8(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp);
static int RM16_ToStringBuf_Off16(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp);

int RM16_ToStringBuf(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp, Prefix addrPrefix)
{
	int res = 0;
    if(mod != MOD_REG)
	{
		res = Prefix_ToStringBuf(buf, addrPrefix);
		buf += res;
	}
	
	switch(mod)
	{
		case MOD_NO_OFFSET:    return res + RM16_ToStringBuf_NoOff(buf, val, mod, regType, rmDisp);
		case MOD_OFFSET_8:     return res + RM16_ToStringBuf_Off8(buf, val, mod, regType, rmDisp);
		case MOD_OFFSET_16_32: return res + RM16_ToStringBuf_Off16(buf, val, mod, regType, rmDisp);
		case MOD_REG:          return Reg_ToStringBuf(buf, val.rm16_mod11, regType);
		
		default: return res;
	}
}

static int RM16_ToStringBuf_NoOff(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp)
{
	switch(val.rm16_mod00)
	{
		case ADDR_BX_SI:  strcpy(buf, "[bx+si]"); return 7;
		case ADDR_BX_DI:  strcpy(buf, "[bx+di]"); return 7;
		case ADDR_BP_SI:  strcpy(buf, "[bp+si]"); return 7;
		case ADDR_BP_DI:  strcpy(buf, "[bp+di]"); return 7;
		case ADDR_SI:     strcpy(buf, "[si]");    return 4;
		case ADDR_DI:     strcpy(buf, "[di]");    return 4;
		case ADDR_DISP16: return MemOff_ToStringBuf(buf, (union MemOffValue)rmDisp.imm16, MOFF16, PREFIX_NONE);
		case ADDR_BX:     strcpy(buf, "[bx]");    return 4;
		
		default: return 0;
	}
}

static int RM16_ToStringBuf_Off8(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp)
{
	char* startBuf = buf;
	
	switch(val.rm16_mod01)
	{
		case ADDR_BX_SI_DISP8:  strcpy(buf, "[bx+si+"); buf += 7; break;
		case ADDR_BX_DI_DISP8:  strcpy(buf, "[bx+di+"); buf += 7; break;
		case ADDR_BP_SI_DISP8:  strcpy(buf, "[bp+si+"); buf += 7; break;
		case ADDR_BP_DI_DISP8:  strcpy(buf, "[bp+di]"); buf += 7; break;
		case ADDR_SI_DISP8:     strcpy(buf, "[si+");    buf += 4; break;
		case ADDR_DI_DISP8:     strcpy(buf, "[di+");    buf += 4; break;
		case ADDR_BP_DISP8:     strcpy(buf, "[bp+");    buf += 4; break;
		case ADDR_BX_DISP8:     strcpy(buf, "[bx+");    buf += 4; break;
		
		default: return 0;
	}
	
	buf += Imm_ToStringBuf(buf, rmDisp, IMM8);
	strcpy(buf, "]");
	buf++;
	
	return buf - startBuf;
}

static int RM16_ToStringBuf_Off16(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp)
{
	char* startBuf = buf;
	
	switch(val.rm16_mod10)
	{
		case ADDR_BX_SI_DISP16:  strcpy(buf, "[bx+si+"); buf += 7; break;
		case ADDR_BX_DI_DISP16:  strcpy(buf, "[bx+di+"); buf += 7; break;
		case ADDR_BP_SI_DISP16:  strcpy(buf, "[bp+si+"); buf += 7; break;
		case ADDR_BP_DI_DISP16:  strcpy(buf, "[bp+di+"); buf += 7; break;
		case ADDR_SI_DISP16:     strcpy(buf, "[si+");    buf += 4; break;
		case ADDR_DI_DISP16:     strcpy(buf, "[di+");    buf += 4; break;
		case ADDR_BP_DISP16:     strcpy(buf, "[bp+");    buf += 4; break;
		case ADDR_BX_DISP16:     strcpy(buf, "[bx+");    buf += 4; break;
		
		default: return 0;
	}
	
	buf += Imm_ToStringBuf(buf, rmDisp, IMM16);
	strcpy(buf, "]");
	buf++;
	
	return buf - startBuf;
}