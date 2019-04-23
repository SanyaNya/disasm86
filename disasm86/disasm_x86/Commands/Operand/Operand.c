#include "Operand.h"

#define GET_MODE_OP(procMode, prefix)   ((prefix == PREFIX_OVERRIDE_OPERAND_SIZE) ^ procMode)
#define GET_MODE_ADDR(procMode, prefix) ((prefix == PREFIX_OVERRIDE_ADDR_SIZE) ^ procMode)

void Operand_GetFullType(OperandFullType* pftype, OperandInfo info, ProcMode procMode, Mod rmMod, Prefix prefix_opsize, Prefix prefix_addrsize)
{
	pftype->type = info.type;
	pftype->rmMod = rmMod;
	
	switch(info.type)
	{
		case OPERAND_REG:
			pftype->subtype.reg = info.mode16_32 ? Reg_SwitchMode16_32(GET_MODE_OP(procMode, prefix_opsize)) : info.subtype.reg;
			break;
		case OPERAND_MEM:
			pftype->subtype.mem = Mem_SwitchMode16_32(GET_MODE_ADDR(procMode, prefix_addrsize));
			break;
        case OPERAND_RM:
			pftype->subtype.rm.type = RM_SwitchMode16_32(GET_MODE_ADDR(procMode, prefix_addrsize));
			pftype->subtype.rm.regType = info.mode16_32 ? Reg_SwitchMode16_32(GET_MODE_OP(procMode, prefix_opsize)) : info.subtype.reg;
			break;
        case OPERAND_IMM:
			pftype->subtype.imm = info.mode16_32 ? Imm_SwitchMode16_32(GET_MODE_OP(procMode, prefix_opsize)) : info.subtype.imm;
			break;
        case OPERAND_OFFSET:
			pftype->subtype.off = info.mode16_32 ? Offset_SwitchMode16_32(GET_MODE_OP(procMode, prefix_opsize)) : info.subtype.off;
			break;
        case OPERAND_MEM_OFFSET:
			pftype->subtype.moff = info.mode16_32 ? MemOff_SwitchMode16_32(GET_MODE_ADDR(procMode, prefix_opsize)) : info.subtype.moff;
			break;
        case OPERAND_FARPTR:
			pftype->subtype.fptr = FarPtr_SwitchMode16_32(GET_MODE_OP(procMode, prefix_opsize));
			break;
	}
}

int Operand_GetVal(const uint8_t* opValPos, Operand* poperand, ModRM modrm)
{
	switch(poperand->ftype.type)
	{
		case OPERAND_REG:        poperand->val.reg = modrm.reg_opExt.reg; return 0;
        case OPERAND_RM:         poperand->val.rm  = modrm.rm;            return 0;
        case OPERAND_IMM:        return Imm_GetVal(opValPos, &poperand->val.imm, poperand->ftype.subtype.imm);
        case OPERAND_OFFSET:     return Offset_GetVal(opValPos, &poperand->val.off, poperand->ftype.subtype.off);
        case OPERAND_MEM_OFFSET: return MemOff_GetVal(opValPos, &poperand->val.moff, poperand->ftype.subtype.moff);
        case OPERAND_FARPTR:     return FarPtr_GetVal(opValPos, &poperand->val.fptr, poperand->ftype.subtype.fptr);
		case OPERAND_MEM:
			if(poperand->ftype.subtype.mem == MEM_TYPE32) poperand->val.mem.mem32 = modrm.rm.rm32;
			else poperand->val.mem.mem16 = modrm.rm.rm16;
			return 0;
			
		default: return 0;
	}
}

int Operand_ToStringBuf(char* buf, union OperandValue val, OperandFullType ftype, SIB sib, union ImmValue rmDisp, Prefix addrPrefix)
{
    switch(ftype.type)
    {
        case OPERAND_REG:        return Reg_ToStringBuf(buf, val.reg, ftype.subtype.reg);
        case OPERAND_MEM:        return Mem_ToStringBuf(buf, val.mem, ftype.subtype.mem, sib, ftype.rmMod, rmDisp, addrPrefix);
        case OPERAND_RM:         return RM_ToStringBuf(buf, val.rm, ftype.subtype.rm, sib, ftype.rmMod, rmDisp, addrPrefix);
        case OPERAND_IMM:        return Imm_ToStringBuf(buf, val.imm, ftype.subtype.imm);
        case OPERAND_OFFSET:     return Offset_ToStringBuf(buf, val.off, ftype.subtype.off);
        case OPERAND_MEM_OFFSET: return MemOff_ToStringBuf(buf, val.moff, ftype.subtype.moff, addrPrefix);
        case OPERAND_FARPTR:     return FarPtr_ToStringBuf(buf, val.fptr, ftype.subtype.fptr);
		
		default: return 0;
    }
}

union OperandFullSubtype Operand_CastSubtypeToFullSubtype(union OperandSubtype subtype, OperandType type)
{
	union OperandFullSubtype res;
	switch(type)
	{
		case OPERAND_REG:        res.reg  = subtype.reg;  return res;
		case OPERAND_IMM:        res.imm  = subtype.imm;  return res;
		case OPERAND_OFFSET:     res.off  = subtype.off;  return res;
		case OPERAND_MEM_OFFSET: res.moff = subtype.moff; return res;
		
		default: return res;
	}
}