#include <string.h>
#include "Base.h"

static int Base_ToStringBuf_NoOff(char* buf, union Base base, union ImmValue rmDisp);
static int Base_ToStringBuf_Off8(char* buf, union Base base, union ImmValue rmDisp);
static int Base_ToStringBuf_Off32(char* buf, union Base base, union ImmValue rmDisp);

int Base_ToStringBuf(char* buf, union Base base, Mod mod, union ImmValue rmDisp)
{
	switch(mod)
	{
		case MOD_NO_OFFSET:    return Base_ToStringBuf_NoOff(buf, base, rmDisp);
		case MOD_OFFSET_8:     return Base_ToStringBuf_Off8(buf, base, rmDisp);
		case MOD_OFFSET_16_32: return Base_ToStringBuf_Off32(buf, base, rmDisp);
		
		default: return 0;
	}
}

static int Base_ToStringBuf_NoOff(char* buf, union Base base, union ImmValue rmDisp)
{
	switch(base.base_mod00)
	{
		case BASE_EAX:    strcpy(buf, "eax"); return 3;
		case BASE_ECX:    strcpy(buf, "ecx"); return 3;
		case BASE_EDX:    strcpy(buf, "edx"); return 3;
		case BASE_EBX:    strcpy(buf, "ebx"); return 3;
		case BASE_ESP:    strcpy(buf, "esp"); return 3;
		case BASE_DISP32: return Imm_ToStringBuf(buf, rmDisp, IMM32);
		case BASE_ESI:    strcpy(buf, "esi"); return 3;
		case BASE_EDI:    strcpy(buf, "edi"); return 3;
		
		default: return 0;
	}
}

static int Base_ToStringBuf_Off8(char* buf, union Base base, union ImmValue rmDisp)
{
	switch(base.base_mod01)
	{
		case BASE_EAX_DISP8: strcpy(buf, "eax+"); break;
		case BASE_ECX_DISP8: strcpy(buf, "ecx+"); break;
		case BASE_EDX_DISP8: strcpy(buf, "edx+"); break;
		case BASE_EBX_DISP8: strcpy(buf, "ebx+"); break;
		case BASE_ESP_DISP8: strcpy(buf, "esp+"); break;
		case BASE_EBP_DISP8: strcpy(buf, "ebp+"); break;
		case BASE_ESI_DISP8: strcpy(buf, "esi+"); break;
		case BASE_EDI_DISP8: strcpy(buf, "edi+"); break;
			
		default: return 0;
	}
	
	return Imm_ToStringBuf(buf+4, rmDisp, IMM8) + 4;
}

static int Base_ToStringBuf_Off32(char* buf, union Base base, union ImmValue rmDisp)
{
	switch(base.base_mod10)
	{
		case BASE_EAX_DISP32: strcpy(buf, "eax+"); break;
		case BASE_ECX_DISP32: strcpy(buf, "ecx+"); break;
		case BASE_EDX_DISP32: strcpy(buf, "edx+"); break;
		case BASE_EBX_DISP32: strcpy(buf, "ebx+"); break;
		case BASE_ESP_DISP32: strcpy(buf, "esp+"); break;
		case BASE_EBP_DISP32: strcpy(buf, "ebp+"); break;
		case BASE_ESI_DISP32: strcpy(buf, "esi+"); break;
		case BASE_EDI_DISP32: strcpy(buf, "edi+"); break;
			
		default: return 0;
	}
	
	return Imm_ToStringBuf(buf+4, rmDisp, IMM32) + 4;
}