#ifndef MEMOFF_H
#define MEMOFF_H

#include <stdint.h>
#include "../../Prefix/Prefix.h"

typedef enum
{
    MOFF8,
    MOFF16,
    MOFF32
} MemOffType;

union MemOffValue
{
    uint8_t  moff8;
    uint16_t moff16;
    uint32_t moff32;
};

int MemOff_ToStringBuf(char* buf, union MemOffValue val, MemOffType type, Prefix prefix);

MemOffType MemOff_SwitchMode16_32(int mode);

int MemOff_GetVal(const uint8_t* opValPos, union MemOffValue* pval, MemOffType type);

#endif