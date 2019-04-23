#ifndef SIB_H
#define SIB_H

#include "Scale.h"
#include "Index/Index.h"
#include "Base/Base.h"
#include "../../../Imm/Imm.h"

#define GET_SIB(byte) {((SIB_Byte)byte).ss, ((SIB_Byte)byte).index, ((SIB_Byte)byte).base}

typedef struct
{
    unsigned base  :3;
	unsigned index :3;
    unsigned ss    :2;
} SIB_Byte;

typedef struct 
{
    Scale       ss;
    union Index index;
    union Base  base;  
} SIB;

int SIB_ToStringBuf(char* buf, SIB sib, Mod mod, union ImmValue rmDisp);

#endif
