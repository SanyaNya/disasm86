#ifndef FARPTR_H
#define FARPTR_H

#include <stdint.h>

typedef enum
{
    FARPTR_16_16,
    FARPTR_16_32
} FarPtrType;

typedef struct
{
    uint16_t seg;
    uint16_t off;
} FarPtr16_16_Value;

typedef struct
{
    uint16_t seg;
    uint32_t off;
} FarPtr16_32_Value;

union FarPtrValue
{
    FarPtr16_16_Value farptr16_16;
    FarPtr16_32_Value farptr16_32;
};

int FarPtr_ToStringBuf(char* buf, union FarPtrValue val, FarPtrType type);

FarPtrType FarPtr_SwitchMode16_32(int mode);

int FarPtr_GetVal(const uint8_t* opValPos, union FarPtrValue* pval, FarPtrType type);

#endif