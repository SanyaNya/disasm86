#ifndef PREFIX_H
#define PREFIX_H

#include <stdint.h>
#include "../../Procs/Procs.h"

typedef enum
{
	CMPRSD_PREFIX_NONE,

    CMPRSD_PREFIX_0F,

    CMPRSD_PREFIX_OVERRIDE_ES,
	CMPRSD_PREFIX_OVERRIDE_CS,
	CMPRSD_PREFIX_OVERRIDE_SS,
	CMPRSD_PREFIX_OVERRIDE_DS,
	CMPRSD_PREFIX_OVERRIDE_FS,
    CMPRSD_PREFIX_OVERRIDE_GS,

	CMPRSD_PREFIX_OVERRIDE_OPERAND_SIZE,
	
	CMPRSD_PREFIX_OVERRIDE_ADDR_SIZE,
	
	CMPRSD_PREFIX_WAIT,
	CMPRSD_PREFIX_LOCK,	
	CMPRSD_PREFIX_REPNZ,
	CMPRSD_PREFIX_REPZ
} CompressedPrefix;

typedef enum
{
	PREFIX_NONE,

    PREFIX_0F = 0x0f,

    PREFIX_OVERRIDE_ES = 0x26,
	PREFIX_OVERRIDE_CS = 0x2e,
	PREFIX_OVERRIDE_SS = 0x36,
	PREFIX_OVERRIDE_DS = 0x3e,
	PREFIX_OVERRIDE_FS = 0x64,
    PREFIX_OVERRIDE_GS = 0x65,

	PREFIX_OVERRIDE_OPERAND_SIZE = 0x66,
	
	PREFIX_OVERRIDE_ADDR_SIZE = 0x67,
	
	PREFIX_WAIT  = 0x9b,
	PREFIX_LOCK  = 0xf0,	
	PREFIX_REPNZ = 0xf2,
	PREFIX_REPZ  = 0xf3
} Prefix;

//Возможные перфиксы команды
//В каждой группе может быть только один префикс
typedef struct
{
	Prefix prefix_0f;
	Prefix prefix_seg;
	Prefix prefix_opsize;
	Prefix prefix_addrsize;
	Prefix prefix_waitLockRep;
} Prefixes;

const char* Prefix_ToString(Prefix prefix);
int Prefix_ToStringBuf(char* buf, Prefix prefix);

//Получает префиксы команды в cmd и сохраняет их в pprefixes
//Возвращает указатель на опкод команды
const uint8_t* GetPrefixes(Prefixes* pprefixes, const uint8_t* cmd, Proc proc, int mayHaveLock);

Prefix GetPrefix(unsigned p);

#endif
