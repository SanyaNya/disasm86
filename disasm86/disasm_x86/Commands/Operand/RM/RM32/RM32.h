#ifndef RM32_H
#define RM32_H

#include <stdint.h>
#include "../ModRM/Mod.h"
#include "../../Reg/Reg.h"
#include "../../Imm/Imm.h"
#include "../../../Prefix/Prefix.h"
#include "SIB/SIB.h"

typedef enum
{
    ADDR_EAX,
    ADDR_ECX,
    ADDR_EDX,
    ADDR_EBX,
    ADDR_SIB,
    ADDR_DISP32,
    ADDR_ESI,
    ADDR_EDI
} RM32_Mod00;

typedef enum
{
    ADDR_EAX_DISP8,
    ADDR_ECX_DISP8,
    ADDR_EDX_DISP8,
    ADDR_EBX_DISP8,
    ADDR_SIB_DISP8,
    ADDR_EBP_DISP8,
    ADDR_ESI_DISP8,
    ADDR_EDI_DISP8
} RM32_Mod01;

typedef enum
{
    ADDR_EAX_DISP32,
    ADDR_ECX_DISP32,
    ADDR_EDX_DISP32,
    ADDR_EBX_DISP32,
    ADDR_SIB_DISP32,
    ADDR_EBP_DISP32,
    ADDR_ESI_DISP32,
    ADDR_EDI_DISP32
} RM32_Mod10;

union RM32_Value
{
    RM32_Mod00      rm32_mod00;
    RM32_Mod01      rm32_mod01;
    RM32_Mod10      rm32_mod10;
    union RegValue  rm32_mod11;
};

int RM32_ToStringBuf(char* buf, union RM32_Value val, Mod mod, RegType regType, SIB sib, union ImmValue rmDisp, Prefix addrPrefix);

#endif
