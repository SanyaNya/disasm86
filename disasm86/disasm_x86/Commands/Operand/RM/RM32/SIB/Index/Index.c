#include <string.h>
#include "Index.h"

static const char* Index_s1_ToString(Index_ss00 i);
static const char* Index_s2_ToString(Index_ss01 i);
static const char* Index_s4_ToString(Index_ss10 i);
static const char* Index_s8_ToString(Index_ss11 i);

const char* Index_ToString(union Index index, Scale scale)
{
	switch(scale)
	{
		case SCALE_1: return Index_s1_ToString(index.index_ss00);
		case SCALE_2: return Index_s2_ToString(index.index_ss01);
		case SCALE_4: return Index_s4_ToString(index.index_ss10);
		case SCALE_8: return Index_s8_ToString(index.index_ss11);
	}
}

int Index_ToStringBuf(char* buf, union Index index, Scale scale)
{
    strcpy(buf, Index_ToString(index, scale));
	return strlen(buf);
}

static const char* Index_s1_ToString(Index_ss00 i)
{
	switch(i)
	{
		case INDEX_EAX:  return "eax";
		case INDEX_ECX:  return "ecx";
		case INDEX_EDX:  return "edx";
		case INDEX_EBX:  return "ebx";
		case INDEX_NONE_SS00: return "";
		case INDEX_EBP:  return "ebp";
		case INDEX_ESI:  return "esi";
		case INDEX_EDI:  return "edi";
	}
}

static const char* Index_s2_ToString(Index_ss01 i)
{
	switch(i)
	{
		case INDEX_EAX_2:  return "2*eax";
		case INDEX_ECX_2:  return "2*ecx";
		case INDEX_EDX_2:  return "2*edx";
		case INDEX_EBX_2:  return "2*ebx";
		case INDEX_NONE_SS01:   return "";
		case INDEX_EBP_2:  return "2*ebp";
		case INDEX_ESI_2:  return "2*esi";
		case INDEX_EDI_2:  return "2*edi";
	}
}

static const char* Index_s4_ToString(Index_ss10 i)
{
	switch(i)
	{
		case INDEX_EAX_4:  return "4*eax";
		case INDEX_ECX_4:  return "4*ecx";
		case INDEX_EDX_4:  return "4*edx";
		case INDEX_EBX_4:  return "4*ebx";
		case INDEX_NONE_SS10:   return "";
		case INDEX_EBP_4:  return "4*ebp";
		case INDEX_ESI_4:  return "4*esi";
		case INDEX_EDI_4:  return "4*edi";
	}
}

static const char* Index_s8_ToString(Index_ss11 i)
{
	switch(i)
	{
		case INDEX_EAX_8:  return "8*eax";
		case INDEX_ECX_8:  return "8*ecx";
		case INDEX_EDX_8:  return "8*edx";
		case INDEX_EBX_8:  return "8*ebx";
		case INDEX_NONE_SS11:   return "";
		case INDEX_EBP_8:  return "8*ebp";
		case INDEX_ESI_8:  return "8*esi";
		case INDEX_EDI_8:  return "8*edi";
	}
}