#ifndef BASE_H
#define BASE_H

#include "../../../ModRM/Mod.h"
#include "../../../../Imm/Imm.h"

typedef enum
{
    BASE_EAX,
    BASE_ECX,
    BASE_EDX,
    BASE_EBX,
    BASE_ESP,
    BASE_DISP32,
    BASE_ESI,
    BASE_EDI
} Base_mod00;

typedef enum
{
    BASE_EAX_DISP8,
    BASE_ECX_DISP8,
    BASE_EDX_DISP8,
    BASE_EBX_DISP8,
    BASE_ESP_DISP8,
    BASE_EBP_DISP8,
    BASE_ESI_DISP8,
    BASE_EDI_DISP8
} Base_mod01;

typedef enum
{
    BASE_EAX_DISP32,
    BASE_ECX_DISP32,
    BASE_EDX_DISP32,
    BASE_EBX_DISP32,
    BASE_ESP_DISP32,
    BASE_EBP_DISP32,
    BASE_ESI_DISP32,
    BASE_EDI_DISP32
} Base_mod10;

union Base
{
    Base_mod00 base_mod00;
    Base_mod01 base_mod01;
    Base_mod10 base_mod10;
};

int Base_ToStringBuf(char* buf, union Base base, Mod mod, union ImmValue rmDisp);

#endif
