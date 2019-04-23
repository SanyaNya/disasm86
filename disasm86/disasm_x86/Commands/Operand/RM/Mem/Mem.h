#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include "../../Imm/Imm.h"
#include "../../../Prefix/Prefix.h"
#include "../RM.h"

union MemValue
{
    union RM16_Value mem16;
    union RM32_Value mem32;   
};

typedef enum
{
    MEM_TYPE16,
    MEM_TYPE32
} MemType;

int Mem_ToStringBuf(char* buf, union MemValue val, MemType type, SIB sib, Mod rmMod, union ImmValue rmDisp, Prefix addrPrefix);

MemType Mem_SwitchMode16_32(int mode);

#endif