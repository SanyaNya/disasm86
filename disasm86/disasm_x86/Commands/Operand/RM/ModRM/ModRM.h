#ifndef MODRM_H
#define MODRM_H

#include "Mod.h"
#include "OpcodeExt.h"
#include "../RM.h"
#include "../../Reg/Reg.h"

#define GET_MODRM(byte) {((ModRM_Byte)byte).mod, ((ModRM_Byte)byte).reg_opExt, ((ModRM_Byte)byte).rm}

//ModRM byte format:
// |Mod|Reg|R\M| - если поле reg/opcode field содержит r
// | 00|000|000|
// 
// |Mod|Opcode ext|R\M| - если поле reg/opcode field содержит число 0-7
// | 00|    000   |000|   Reg заменяется на Opcode ext(расширение опкода)
//
// ModRM осутствует - если поле reg/opcode field ничего не содкржит

union Reg_OpcodeExt
{
    union RegValue reg;
    OpcodeExt      opcode; 
};

typedef enum
{
    NO_MODRM,
    CONTAINS_MODRM,
    REG_OPCODE
} ModRM_Type;

typedef struct
{
    unsigned rm        :3;
    unsigned reg_opExt :3;
    unsigned mod       :2;
} ModRM_Byte;

typedef struct
{
    Mod                 mod;
    union Reg_OpcodeExt reg_opExt;
    union RM_Value      rm;
} ModRM;

#endif
