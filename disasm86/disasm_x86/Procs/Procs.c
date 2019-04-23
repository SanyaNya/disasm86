#include <string.h>
#include "Procs.h"

int Procs_CompatibleWith(Proc proc, Proc other)
{
	return proc <= PROC_AFTER_C7 && other <= PROC_AFTER_C7 && proc >= other || proc == other;
}

Proc Proc_Parse(const char* str)
{
	if(!strcmp(str, "00+"))       return PROC_AFTER_00;
	else if(!strcmp(str, "01+"))  return PROC_AFTER_01;
	else if(!strcmp(str, "02+"))  return PROC_AFTER_02;
	else if(!strcmp(str, "03+"))  return PROC_AFTER_03;
	else if(!strcmp(str, "03++")) return PROC_AFTER_03_LATER_REVISIONS;
	else if(!strcmp(str, "04+"))  return PROC_AFTER_04;
	else if(!strcmp(str, "04++")) return PROC_AFTER_04_LATER_REVISIONS;
	else if(!strcmp(str, "px+"))  return PROC_AFTER_PX;
	else if(!strcmp(str, "pp+"))  return PROC_AFTER_PP;
	else if(!strcmp(str, "p2+"))  return PROC_AFTER_P2;
	else if(!strcmp(str, "p3+"))  return PROC_AFTER_P3;
	else if(!strcmp(str, "p4+"))  return PROC_AFTER_P4;
	else if(!strcmp(str, "p4++")) return PROC_AFTER_P4_LATER_REVISIONS;
	else if(!strcmp(str, "c1+"))  return PROC_AFTER_C1;
	else if(!strcmp(str, "c2+"))  return PROC_AFTER_C2;
	else if(!strcmp(str, "c2++")) return PROC_AFTER_C2_LATER_REVISIONS;
	else if(!strcmp(str, "c7+"))  return PROC_AFTER_C7;
	else return PROC_UNKNOWN;
}

ProcMode ProcMode_Parse(const char* str)
{
	if(!strcmp(str, "16"))      return PROC_MODE16;
	else if(!strcmp(str, "32")) return PROC_MODE32;
	else return PROC_MODE_UNKNOWN;
}