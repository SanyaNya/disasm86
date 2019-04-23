#ifndef DISASM_X86_H
#define DISASM_X86_H

#include <stdint.h>
#include "Procs/Procs.h"

//Запись в buf дизассемблировнной инструкции(префиксы, название команды, аргументы) по адресу instr
//Возвращащет длину строки дизассемблированной инструкци
//В *lastPos записывается указатель на позицию после команды
int disasm_x86(char* buf, const uint8_t* instr, Proc proc, ProcMode procMode, const uint8_t** lastPos);

int Data_ToStringBuf(char* buf, const uint8_t* instr, const uint8_t* cmd);
int Hex_ToStringBuf(char* buf, const uint8_t* pos, const uint8_t* end);

#endif
