#ifndef OPERAND_H
#define OPERAND_H

#include <stdint.h>
#include "../../Procs/Procs.h"
#include "Reg/Reg.h"
#include "RM/RM.h"
#include "RM/ModRM/ModRM.h"
#include "RM/Mem/Mem.h"
#include "Imm/Imm.h"
#include "Offset/Offset.h"
#include "MemOff/MemOff.h"
#include "FarPtr/FarPtr.h"

#define GET_OPERAND_INFO(byte) {((OperandInfo_Byte)byte).type, ((OperandInfo_Byte)byte).subtype, ((OperandInfo_Byte)byte).mode16_32}

typedef enum
{
    OPERAND_REG,
    OPERAND_MEM,
    OPERAND_RM,
    OPERAND_IMM,
    OPERAND_OFFSET,
    OPERAND_MEM_OFFSET,
    OPERAND_FARPTR
} OperandType;

union OperandSubtype
{
    RegType     reg;
    ImmType     imm;
    OffsetType  off;
    MemOffType  moff;
};

union OperandFullSubtype
{
    RegType     reg;
    MemType     mem;
    RM_FullType rm;
    ImmType     imm;
    OffsetType  off;
    MemOffType  moff;
    FarPtrType  fptr;
};

union OperandValue
{
    union RegValue    reg;
    union MemValue    mem;
    union RM_Value    rm;
    union ImmValue    imm;
    union OffsetValue off;
    union MemOffValue moff;
    union FarPtrValue fptr;
};

typedef struct
{
    OperandType              type;
    union OperandFullSubtype subtype;
    Mod                      rmMod;
} OperandFullType;

typedef struct
{
	union OperandValue val;
	OperandFullType    ftype;
} Operand;

typedef struct
{
    unsigned type       :3;
    unsigned subtype    :4;
    unsigned mode16_32  :1;
} OperandInfo_Byte;

typedef struct
{
    OperandType          type;
    union OperandSubtype subtype;
    int                  mode16_32;
} OperandInfo;

void Operand_GetFullType(OperandFullType* pftype, OperandInfo info, ProcMode procMode, Mod rmMod, Prefix prefix_opsize, Prefix prefix_addrsize);

int Operand_GetVal(const uint8_t* opValPos, Operand* poperand, ModRM modrm);

int Operand_ToStringBuf(char* buf, union OperandValue val, OperandFullType ftype, SIB sib, union ImmValue rmDisp, Prefix addrPrefix);

union OperandFullSubtype Operand_CastSubtypeToFullSubtype(union OperandSubtype subtype, OperandType type);

#endif