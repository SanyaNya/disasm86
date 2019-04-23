#ifndef RM_H
#define RM_H

#include <stdint.h>
#include "../Imm/Imm.h"
#include "../Reg/Reg.h"
#include "../../Prefix/Prefix.h"
#include "RM16/RM16.h"
#include "RM32/RM32.h"
#include "ModRM/Mod.h"

union RM_Value
{
    union RM16_Value rm16;
    union RM32_Value rm32;
};

typedef enum
{
    RM_TYPE16,
    RM_TYPE32
} RM_Type;

typedef struct
{
	RM_Type type;
	RegType regType;
} RM_FullType;

int RM_ToStringBuf(char* buf, union RM_Value val, RM_FullType ftype, SIB sib, Mod rmMod, union ImmValue rmDisp, Prefix addrPrefix);

RM_Type RM_SwitchMode16_32(int mode);

#endif
