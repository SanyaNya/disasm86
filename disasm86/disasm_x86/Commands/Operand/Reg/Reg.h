#ifndef REG_H
#define REG_H

typedef enum
{
    REG_AL,
    REG_CL,
    REG_DL,
    REG_BL,
    REG_AH,
    REG_CH,
    REG_DH,
    REG_BH
} Reg_r8;

typedef enum
{
    REG_AX,
    REG_CX,
    REG_DX,
    REG_BX,
    REG_SP,
    REG_BP,
    REG_SI,
    REG_DI
} Reg_r16;

typedef enum
{
    REG_EAX,
    REG_ECX,
    REG_EDX,
    REG_EBX,
    REG_ESP,
    REG_EBP,
    REG_ESI,
    REG_EDI
} Reg_r32;

typedef enum
{
    REG_MM0,
    REG_MM1,
    REG_MM2,
    REG_MM3,
    REG_MM4,
    REG_MM5,
    REG_MM6,
    REG_MM7
} Reg_mm;

typedef enum
{
    REG_XMM0,
    REG_XMM1,
    REG_XMM2,
    REG_XMM3,
    REG_XMM4,
    REG_XMM5,
    REG_XMM6,
    REG_XMM7
} Reg_xmm;

typedef enum
{
    REG_ES,
    REG_CS,
    REG_SS,
    REG_DS,
    REG_FS,
    REG_GS,
    REG_SREG6,
    REG_SREG7
} Reg_sreg;

typedef enum
{
    REG_CR0,
    REG_CR1,
    REG_CR2,
    REG_CR3,
    REG_CR4,
    REG_CR5,
    REG_CR6,
    REG_CR7
} Reg_creg;

typedef enum
{
    REG_DR0,
    REG_DR1,
    REG_DR2,
    REG_DR3,
    REG_DR4,
    REG_DR5,
    REG_DR6,
    REG_DR7
} Reg_dreg;

typedef enum
{
    REG_ST0,
    REG_ST1,
    REG_ST2,
    REG_ST3,
    REG_ST4,
    REG_ST5,
    REG_ST6,
    REG_ST7
} Reg_st;

union RegValue
{
    Reg_r8   r8;
    Reg_r16  r16;
    Reg_r32  r32;
    Reg_mm   mm;
    Reg_xmm  xmm;
    Reg_sreg sreg;
    Reg_creg creg;
    Reg_dreg dreg;
    Reg_st   st;
};

typedef enum
{
    REG_TYPE_R8,
    REG_TYPE_R16,
    REG_TYPE_R32,
    REG_TYPE_MM,
    REG_TYPE_XMM,
    REG_TYPE_SREG,
    REG_TYPE_CREG,
    REG_TYPE_DREG,
    REG_TYPE_ST
} RegType;

const char* Reg_ToString(union RegValue val, RegType type);
int Reg_ToStringBuf(char* buf, union RegValue val, RegType type);
RegType Reg_SwitchMode16_32(int mode);

#endif
