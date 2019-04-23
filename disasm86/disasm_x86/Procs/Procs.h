#ifndef PROCS_H
#define PROCS_H

//Список процессоров x86
typedef enum
{
    PROC_AFTER_00,  //8086
    PROC_AFTER_01,  //80186
    PROC_AFTER_02,  //80286
    PROC_AFTER_03,  //80386
    PROC_AFTER_03_LATER_REVISIONS,
    PROC_AFTER_04,  //80486
	PROC_AFTER_04_LATER_REVISIONS,
    PROC_AFTER_P1,  //Pentium (1)
	PROC_AFTER_P2_LATER_REVISIONS,
    PROC_AFTER_PX,  //Pentium MMX
    PROC_AFTER_PP,  //Pentium Pro
    PROC_AFTER_P2,  //Pentium 2
    PROC_AFTER_P3,  //Pentium 3
    PROC_AFTER_P4,  //Pentium 4
	PROC_AFTER_P4_LATER_REVISIONS,
    PROC_AFTER_C1,  //Core (1)
    PROC_AFTER_C2,  //Core 2
	PROC_AFTER_C2_LATER_REVISIONS,
    PROC_AFTER_C7,  //Core 7
	PROC_ONLY_00,
	PROC_ONLY_02,
	
	PROC_UNKNOWN
} Proc;

//Режим процессора
typedef enum
{
	PROC_MODE16,
	PROC_MODE32,
	
	PROC_MODE_UNKNOWN
} ProcMode;

int Procs_CompatibleWith(Proc proc, Proc other);

Proc Proc_Parse(const char* str);
ProcMode ProcMode_Parse(const char* str);

#endif
