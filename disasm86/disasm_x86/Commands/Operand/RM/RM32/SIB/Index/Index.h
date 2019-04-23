#ifndef INDEX_H
#define INDEX_H

#include "../Scale.h"

typedef enum
{
    INDEX_EAX,
    INDEX_ECX,
    INDEX_EDX,
    INDEX_EBX,
    INDEX_NONE_SS00,
    INDEX_EBP,
    INDEX_ESI,
    INDEX_EDI
} Index_ss00;

typedef enum
{
    INDEX_EAX_2,
    INDEX_ECX_2,
    INDEX_EDX_2,
    INDEX_EBX_2,
    INDEX_NONE_SS01,
    INDEX_EBP_2,
    INDEX_ESI_2,
    INDEX_EDI_2
} Index_ss01;

typedef enum
{
    INDEX_EAX_4,
    INDEX_ECX_4,
    INDEX_EDX_4,
    INDEX_EBX_4,
    INDEX_NONE_SS10,
    INDEX_EBP_4,
    INDEX_ESI_4,
    INDEX_EDI_4
} Index_ss10;

typedef enum
{
    INDEX_EAX_8,
    INDEX_ECX_8,
    INDEX_EDX_8,
    INDEX_EBX_8,
    INDEX_NONE_SS11,
    INDEX_EBP_8,
    INDEX_ESI_8,
    INDEX_EDI_8
} Index_ss11;

union Index
{
    Index_ss00 index_ss00;
    Index_ss01 index_ss01;
    Index_ss10 index_ss10;
    Index_ss11 index_ss11;
};

const char* Index_ToString(union Index index, Scale scale);
int Index_ToStringBuf(char* buf, union Index index, Scale scale);

#endif
