#ifndef IMM_H
#define IMM_H

#include <stdint.h>

typedef enum
{
    IMM8,
    IMM16,
    IMM32
} ImmType;

union ImmValue
{
    uint8_t  imm8;
    uint16_t imm16;
    uint32_t imm32;
};

int Imm_ToStringBuf(char* buf, union ImmValue val, ImmType type);

ImmType Imm_SwitchMode16_32(int mode);

int Imm_GetVal(const uint8_t* opValPos, union ImmValue* pval, ImmType type);

#endif