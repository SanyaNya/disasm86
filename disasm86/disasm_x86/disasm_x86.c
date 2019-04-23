#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Commands/Commands.h"
#include "disasm_x86.h"

static const uint8_t* InitOperands(CommandFullInfo* pcmdFullInfo, SIB* psib, CommandInfo cmdInfo, const uint8_t* opcodePos, union ImmValue* pdisp, ModRM_Type modrmType, ProcMode procMode, Prefixes prefixes);

int disasm_x86(char* buf, const uint8_t* instr, Proc proc, ProcMode procMode, const uint8_t** lastPos)
{
	CommandInfo cmdInfo;
	CommandFullInfo cmdFullInfo;
	Prefixes prefixes;
	SIB sib;
	
	//Получаем префиксы команды, cmd указывает на опкод
	const uint8_t* cmd = GetPrefixes(&prefixes, instr, proc, cmdInfo.mayHaveLock);

	*lastPos = cmd+1;

	//Получаем информацию о команде из таблицы
	if(!Command_Find(&cmdInfo, proc, cmd, prefixes))
	{
		cmdFullInfo.beforeCmdPrefix = prefixes.prefix_waitLockRep;
		cmdFullInfo.addrPrefix = prefixes.prefix_seg;
		cmdFullInfo.mnemonic = cmdInfo.mnemonic;
		cmdFullInfo.operandsCount = cmdInfo.operandsCount;

		*lastPos = InitOperands(&cmdFullInfo, &sib, cmdInfo, cmd, &cmdFullInfo.rmDisp, cmdInfo.modRmType, procMode, prefixes);

		return Command_ToStringBuf(buf, cmdFullInfo, sib);
	}
	else return Data_ToStringBuf(buf, instr, cmd); //Если команда не найдена, то строка - db byte1, byte2...
}

static int Get_ModRM_SIB_Disp(const uint8_t* modRmPos, ModRM* pmodrm, SIB* psib, union ImmValue* pdisp, ModRM_Type modRmType, ProcMode procMode, Prefix prefix_addrsize)
{
	if(modRmType == NO_MODRM) return 0;

	ModRM modrm = GET_MODRM(*(const ModRM_Byte*)modRmPos);
	*pmodrm = modrm;	
	modRmPos++;
	
	if(modrm.mod == MOD_REG) return 1;
	
	if(procMode == PROC_MODE32 && prefix_addrsize == PREFIX_NONE)
	{
		switch(modrm.mod)
		{
			case MOD_NO_OFFSET:
				if(modrm.rm.rm32.rm32_mod00 == ADDR_SIB)
				{
					SIB sib = GET_SIB(*(const SIB_Byte*)modRmPos);
					*psib = sib;
					modRmPos++;
					
					if(sib.base.base_mod00 == BASE_DISP32)
					{
						pdisp->imm32 = *((uint32_t*)modRmPos);
						return 6;
					}
					
					return 2;
				}
				else if(modrm.rm.rm32.rm32_mod00 == ADDR_DISP32)
                {
				    pdisp->imm32 = *((uint32_t*)modRmPos);

				    return 5;
                }
				
				return 1;
				
			case MOD_OFFSET_8:
				if(modrm.rm.rm32.rm32_mod01 == ADDR_SIB_DISP8)
				{
					SIB sib = GET_SIB(*(const SIB_Byte*)modRmPos);
					*psib = sib;
					modRmPos++;
					
					pdisp->imm8 = *modRmPos;
					
					return 3;
				}
				
				pdisp->imm8 = *modRmPos;
				
				return 2;
				
			case MOD_OFFSET_16_32:
				if(modrm.rm.rm32.rm32_mod10 == ADDR_SIB_DISP32)
				{
					SIB sib = GET_SIB(*(const SIB_Byte*)modRmPos);
					*psib = sib;
					modRmPos++;
					
					pdisp->imm32 = *((uint32_t*)modRmPos);
					
					return 6;
				}
				
				pdisp->imm32 = *((uint32_t*)modRmPos);
				
				return 5;
		}
	}
	else
	{
		switch(modrm.mod)
		{
			case MOD_NO_OFFSET:
				if(modrm.rm.rm16.rm16_mod00 == ADDR_DISP16)
				{
					pdisp->imm16 = *((uint16_t*)modRmPos);
					
					return 3;
				}
				
				return 1;
			case MOD_OFFSET_8:
				pdisp->imm8 = *modRmPos;
				return 2;
			case MOD_OFFSET_16_32:
				pdisp->imm16 = *((uint16_t*)modRmPos);
				return 3;
		}
	}
}

static const uint8_t* InitOperands(CommandFullInfo* pcmdFullInfo, SIB* psib, CommandInfo cmdInfo, const uint8_t* opcodePos, union ImmValue* pdisp, ModRM_Type modrmType, ProcMode procMode, Prefixes prefixes)
{
	const uint8_t* operandValuesPos = opcodePos + Command_HaveSecondByteOp(cmdInfo.prefix_0f, cmdInfo.opcodes[0]) + 1;
	ModRM modrm;
	operandValuesPos += Get_ModRM_SIB_Disp(operandValuesPos, &modrm, psib, pdisp, cmdInfo.modRmType, procMode, prefixes.prefix_addrsize);	
	
	for(int x = 0; x < cmdInfo.operandsCount; x++)
	{
		Operand_GetFullType(&pcmdFullInfo->operands[x].ftype, cmdInfo.operands[x], procMode, modrm.mod, prefixes.prefix_opsize, prefixes.prefix_addrsize);
		if(x != cmdInfo.specOpIndex) operandValuesPos += Operand_GetVal(operandValuesPos, &pcmdFullInfo->operands[x], modrm);
		else                         pcmdFullInfo->operands[x].val = cmdInfo.specOpVal;
	}
	
	return operandValuesPos;
}

int Data_ToStringBuf(char* buf, const uint8_t* instr, const uint8_t* cmd)
{
	char* startBuf = buf;
	
	strcpy(buf, "db ");
	buf += 3;
	
	while(1)
	{
		buf += Imm_ToStringBuf(buf, *(union ImmValue*)instr, IMM8);
		
		if(instr != cmd)
		{
			strcpy(buf, ", ");
			buf += 2;
		}
		else break;

		instr++;
	}
	
	return buf - startBuf;
}

int Hex_ToStringBuf(char* buf, const uint8_t* pos, const uint8_t* end)
{
    char* startBuf = buf;

    for(; pos != end; pos++)
    {
        buf += sprintf(buf, "%2" PRIX8, *pos);
        if(*(buf-2) == ' ') *(buf-2) = '0';
    }

    return buf - startBuf;
}