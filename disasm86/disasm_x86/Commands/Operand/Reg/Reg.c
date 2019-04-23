#include <string.h>
#include "Reg.h"

static const char* R8_ToString(union RegValue val);
static const char* R16_ToString(union RegValue val);
static const char* R32_ToString(union RegValue val);
static const char* MM_ToString(union RegValue val);
static const char* XMM_ToString(union RegValue val);
static const char* SREG_ToString(union RegValue val);
static const char* CREG_ToString(union RegValue val);
static const char* DREG_ToString(union RegValue val);
static const char* ST_ToString(union RegValue val);

const char* Reg_ToString(union RegValue val, RegType type)
{
    switch(type)
    {
        case REG_TYPE_R8:   return R8_ToString(val);
        case REG_TYPE_R16:  return R16_ToString(val);
        case REG_TYPE_R32:  return R32_ToString(val);
        case REG_TYPE_MM:   return MM_ToString(val);
        case REG_TYPE_XMM:  return XMM_ToString(val);
        case REG_TYPE_SREG: return SREG_ToString(val);
        case REG_TYPE_CREG: return CREG_ToString(val);
        case REG_TYPE_DREG: return DREG_ToString(val);
        case REG_TYPE_ST:   return ST_ToString(val);
        
        default:            return "";
    }
}

int Reg_ToStringBuf(char* buf, union RegValue val, RegType type)
{
    strcpy(buf, Reg_ToString(val, type));
	return strlen(buf);
}

RegType Reg_SwitchMode16_32(int mode)
{
	return REG_TYPE_R16 + mode;
}

static const char* R8_ToString(union RegValue val)
{
    switch (val.r8)
    {
        case REG_AL: return "al";
        case REG_CL: return "cl";
        case REG_DL: return "dl";
        case REG_BL: return "bl";
        case REG_AH: return "ah";
        case REG_CH: return "ch";
        case REG_DH: return "dh";
        case REG_BH: return "bh";
		
		default: return "";
    }
}

static const char* R16_ToString(union RegValue val)
{
    switch (val.r16)
    {
        case REG_AX: return "ax";
        case REG_CX: return "cx";
        case REG_DX: return "dd";
        case REG_BX: return "bx";
        case REG_SP: return "sp";
        case REG_BP: return "bp";
        case REG_SI: return "si";
        case REG_DI: return "di";
				
		default: return "";
    }
}

static const char* R32_ToString(union RegValue val)
{
    switch (val.r32)
    {
        case REG_EAX: return "eax";
        case REG_ECX: return "ecx";
        case REG_EDX: return "edx";
        case REG_EBX: return "ebx";
        case REG_ESP: return "esp";
        case REG_EBP: return "ebp";
        case REG_ESI: return "esi";
        case REG_EDI: return "edi";
				
		default: return "";
    }
}

static const char* MM_ToString(union RegValue val)
{
    switch (val.mm)
    {
        case REG_MM0: return "mm0";
        case REG_MM1: return "mm1";
        case REG_MM2: return "mm2";
        case REG_MM3: return "mm3";
        case REG_MM4: return "mm4";
        case REG_MM5: return "mm5";
        case REG_MM6: return "mm6";
        case REG_MM7: return "mm7";
				
		default: return "";
    }
}

static const char* XMM_ToString(union RegValue val)
{
    switch (val.xmm)
    {
        case REG_XMM0: return "xmm0";
        case REG_XMM1: return "xmm1";
        case REG_XMM2: return "xmm2";
        case REG_XMM3: return "xmm3";
        case REG_XMM4: return "xmm4";
        case REG_XMM5: return "xmm5";
        case REG_XMM6: return "xmm6";
        case REG_XMM7: return "xmm7";
				
		default: return "";
    }
}

static const char* SREG_ToString(union RegValue val)
{
    switch (val.sreg)
    {
        case REG_ES:    return "es";
        case REG_CS:    return "cs";
        case REG_SS:    return "ss";
        case REG_DS:    return "ds";
        case REG_FS:    return "fs";
        case REG_GS:    return "gs";
        case REG_SREG6: return "sreg6";
        case REG_SREG7: return "sreg7";
				
		default: return "";
    }
}

static const char* CREG_ToString(union RegValue val)
{
    switch (val.creg)
    {
        case REG_CR0: return "cr0";
        case REG_CR1: return "cr1";
        case REG_CR2: return "cr2";
        case REG_CR3: return "cr3";
        case REG_CR4: return "cr4";
        case REG_CR5: return "cr5";
        case REG_CR6: return "cr6";
        case REG_CR7: return "cr7";
				
		default: return "";
    }
}

static const char* DREG_ToString(union RegValue val)
{
    switch (val.dreg)
    {
        case REG_DR0: return "dr0";
        case REG_DR1: return "dr1";
        case REG_DR2: return "dr2";
        case REG_DR3: return "dr3";
        case REG_DR4: return "dr4";
        case REG_DR5: return "dr5";
        case REG_DR6: return "dr6";
        case REG_DR7: return "dr7";
				
		default: return "";
    }
}

static const char* ST_ToString(union RegValue val)
{
    switch(val.st)
    {
        case REG_ST0: return "st0";
        case REG_ST1: return "st1";
        case REG_ST2: return "st2";
        case REG_ST3: return "st3";
        case REG_ST4: return "st4";
        case REG_ST5: return "st5";
        case REG_ST6: return "st6";
        case REG_ST7: return "st7";
				
		default: return "";
    }
}