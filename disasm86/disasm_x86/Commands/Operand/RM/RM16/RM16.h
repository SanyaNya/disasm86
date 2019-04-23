#ifndef RM16_H
#define RM16_H

#include "../ModRM/Mod.h"
#include "../../Reg/Reg.h"
#include "../../../Prefix/Prefix.h"
#include "../../Imm/Imm.h"

typedef enum
{
    ADDR_BX_SI,
    ADDR_BX_DI,
    ADDR_BP_SI,
    ADDR_BP_DI,
    ADDR_SI,
    ADDR_DI,
    ADDR_DISP16,
    ADDR_BX
} RM16_Mod00;

typedef enum
{
    ADDR_BX_SI_DISP8,
    ADDR_BX_DI_DISP8,
    ADDR_BP_SI_DISP8,
    ADDR_BP_DI_DISP8,
    ADDR_SI_DISP8,
    ADDR_DI_DISP8,
    ADDR_BP_DISP8,
    ADDR_BX_DISP8
} RM16_Mod01;

typedef enum
{
    ADDR_BX_SI_DISP16,
    ADDR_BX_DI_DISP16,
    ADDR_BP_SI_DISP16,
    ADDR_BP_DI_DISP16,
    ADDR_SI_DISP16,
    ADDR_DI_DISP16,
    ADDR_BP_DISP16,
    ADDR_BX_DISP16
} RM16_Mod10;

union RM16_Value
{
    RM16_Mod00      rm16_mod00;
    RM16_Mod01      rm16_mod01;
    RM16_Mod10      rm16_mod10;
    union RegValue  rm16_mod11;
};

int RM16_ToStringBuf(char* buf, union RM16_Value val, Mod mod, RegType regType, union ImmValue rmDisp, Prefix addrPrefix);

#endif
