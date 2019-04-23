#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>
#include "Prefix/Prefix.h"
#include "Operand/Operand.h"
#include "../Procs/Procs.h"

#define GET_COMMAND_INFO(cmprsd)                                                   \
OperandInfo op1 = GET_OPERAND_INFO(((Compresssed_CommandInfo)cmprsd).operands[0]); \
OperandInfo op2 = GET_OPERAND_INFO(((Compresssed_CommandInfo)cmprsd).operands[1]); \
OperandInfo op3 = GET_OPERAND_INFO(((Compresssed_CommandInfo)cmprsd).operands[2]); \
CommandInfo cmdInfo =                                                              \
{                                                                                  \
	GetPrefix((CompressedPrefix)((Compresssed_CommandInfo)cmprsd).cmdPrefix),      \
	((Compresssed_CommandInfo)cmprsd).prefix_0f,                                   \
	((Compresssed_CommandInfo)cmprsd).secondOp,                                    \
	((Compresssed_CommandInfo)cmprsd).modRmType,                                   \
	((Compresssed_CommandInfo)cmprsd).proc,                                        \
	((Compresssed_CommandInfo)cmprsd).operandsCount,                               \
	((Compresssed_CommandInfo)cmprsd).mayHaveLock,                                 \
	((Compresssed_CommandInfo)cmprsd).regExtVal,                                   \
	((Compresssed_CommandInfo)cmprsd).specOpIndex,                                 \
	((Compresssed_CommandInfo)cmprsd).specOpVal,                                   \
	{((Compresssed_CommandInfo)cmprsd).opcodes[0],                                 \
	((Compresssed_CommandInfo)cmprsd).opcodes[1]},                                 \
	{                                                                              \
		op1,                                                                       \
		op2,                                                                       \
		op3                                                                        \
	},                                                                             \
	((Compresssed_CommandInfo)cmprsd).mnemonic                                     \
}

//Информация о команде из таблицы
typedef struct
{
    unsigned           cmdPrefix     :4; //Обязательный перфикс команды
    unsigned           prefix_0f     :1; //Наличие префикса 0f
    unsigned           secondOp      :1; //Наличие второго байта опкода(это константный байт modrm или второй опкод, наличие которого определяется функцией Command_HaveSecondByteOp())
    unsigned           modRmType     :2; //Наличие байта modrm, поле reg или opcode extension

    unsigned           proc          :5; //Требуемый процессор
    unsigned           operandsCount :2; //Кол-во операндов
	unsigned           mayHaveLock   :1; //Может ли команда иметь префикс LOCK
	
	unsigned           regExtVal     :3; //Значение opcode extension если он есть в modrm
    unsigned           specOpIndex   :2; //Индекс операнда, который является константой, если его нет то равен 4
    unsigned           specOpVal     :3; //Значение константного операнда если есть

    uint8_t            opcodes[2];       //opcodes[0] - опкод, opcodes[1] - константный modrm или байт после опкода если есть
    OperandInfo_Byte   operands[3];      //Типы операндов
    const char*        mnemonic;         //Мнемоника команды
} Compresssed_CommandInfo;

//Информация о команде из таблицы
typedef struct
{
    Prefix             cmdPrefix;
    int                prefix_0f;
    int                secondOp;
    ModRM_Type         modRmType;

    Proc               proc;
    uint8_t            operandsCount;
	int                mayHaveLock;
	
	uint8_t            regExtVal;
    uint8_t            specOpIndex;
    union OperandValue specOpVal;

    uint8_t            opcodes[2];
    OperandInfo        operands[3];
    const char*        mnemonic;
} CommandInfo;

//Информация о команде необходимая для получения строки
typedef struct
{
	Prefix beforeCmdPrefix; //Префикс стоящий перед мнемоникой
	Prefix addrPrefix;      //Префикс стоящий в адресе
	
	const char* mnemonic;   //Мнемоника
	
	int operandsCount;      //Кол-во операндов
	Operand operands[3];    //Типы и значения операндов
		
	union ImmValue rmDisp;  //Значение disp в адресе если есть
} CommandFullInfo;

void Command_GenerateGrps();

//Находит команду в таблице и сохраняет ее в pinfo
//cmd      - указатель на опкод
//prefixes - префиксы команды
//Если команда не найдена возвращает 1, иначе - 0
int Command_Find(CommandInfo* pinfo, Proc proc, const uint8_t* cmd, Prefixes prefixes);

//Преобразует информацию о команде в строку
//buf - указатель на место, куда будет записываться строка
//cmd - информация о команде
//Возвращает длину строки
int Command_ToStringBuf(char* buf, CommandFullInfo cmd, SIB sib);

/*
//Является ли команда строковой
//prefix_0f - наличие префикса 0f
//op        - опкод
int Command_IsStrOp(int prefix_0f, uint8_t op);*/

//Есть ли у команды второй опкод
//prefix_0f - наличие префикса 0f
//op        - опкод
int Command_HaveSecondByteOp(int prefix_0f, uint8_t op);

#endif
