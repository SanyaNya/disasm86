#ifndef OFFSET_H
#define OFFSET_H

#include <stdint.h>

#define OFFSET_STR_MAXSIZE 14

typedef enum
{
    OFF8,
    OFF16,
    OFF32
} OffsetType;

union OffsetValue
{
    uint8_t  off8;
    uint16_t off16;
    uint32_t off32;
};

int Offset_ToStringBuf(char* buf, union OffsetValue val, OffsetType type);

OffsetType Offset_SwitchMode16_32(int mode);

int Offset_GetVal(const uint8_t* opValPos, union OffsetValue* pval, OffsetType type);

#endif