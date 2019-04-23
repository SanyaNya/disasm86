#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "disasm_x86/disasm_x86.h"

#define FILE_BUFSIZE 4096

//Последние 15 байт всегда 0, для того чтобы дизассемблер не выходил за пределы
int size;
uint8_t mem[FILE_BUFSIZE+15];
char strbuf[256];

Proc proc = PROC_AFTER_C7;
ProcMode procMode = PROC_MODE32;
FILE* file = 0;

int ParseArgs(int argc, char* argv[])
{	
	for(int x = 1; x < argc-1; x++)
	{
		if(!strcmp(argv[x], "-p"))
		{
			proc = Proc_Parse(argv[++x]);
			if(proc == PROC_UNKNOWN) printf("Unknown processor \"%s\"\n", argv[x]);
		}
		else if(!strcmp(argv[x], "-m"))
		{
			procMode = ProcMode_Parse(argv[++x]);
			if(proc == PROC_MODE_UNKNOWN) printf("Unknown processor mode \"%s\"\n", argv[x]);
		}
		else if(!strcmp(argv[x], "-f"))
		{
			file = fopen(argv[++x], "rb");
			if(file == 0) printf("Cannot open file \"%s\"\n", argv[x]);
		}
		else printf("Unknown argument \"%s\"\n", argv[x]);
	}
	
	return proc == PROC_UNKNOWN || procMode == PROC_MODE_UNKNOWN || file == 0;
}

int main(int argc, char* argv[])
{	
	if(argc > 1 && !strcmp(argv[1], "-help"))
	{
		printf("disasm86 -f PATH [-p PROC] [-m MODE]\n\n");
		
		printf("PATH - path to file\n\n");
		
		printf("PROC possible values(default - c7+):\n");
		printf(" 00+  - 8086\n");
		printf(" 01+  - 8186\n");
		printf(" 02+  - 8286\n");
		printf(" 03+  - 8386\n");
		printf(" 03++ - 8386 later revisions\n");
		printf(" 04+  - 8486\n");
		printf(" 04++ - 8486 later revisions\n");
		printf(" px+  - Pentium MMX\n");
		printf(" pp+  - Pentium Pro\n");
		printf(" p2+  - Pentium 2\n");
		printf(" p3+  - Pentium 3\n");
		printf(" p4+  - Pentium 4\n");
		printf(" p4++ - Pentium 4 later revisions\n");
		printf(" c1+  - Core\n");
		printf(" c2+  - Core 2\n");
		printf(" c2++ - Core 2 later revisions\n");
		printf(" c7+  - Core 7\n\n");
		
		printf("MODE possible values(default - 32):\n");
		printf(" 16 - 16bit processor mode\n");
		printf(" 32 - 32bit processor mode\n\n");
		
		return 0;
	}

	if(ParseArgs(argc, argv))
	{
		printf("Incorrect args\n");
		printf("Type -help for info\n");
		return 0;
	}
	
	size = fread(mem, 1, FILE_BUFSIZE, file);
	memset(mem+size, 0, 15);
	const uint8_t* lastPos = mem;
	
	uint32_t filePos = 0;

	while(1)
	{
	    const uint8_t* prevPos = lastPos;

        int len = disasm_x86(strbuf, lastPos, proc, procMode, &lastPos);
		
		if(lastPos > mem+size)
		{
			int sz = (mem+size)-prevPos;
			memcpy(mem, prevPos, sz);
			size = fread(mem+sz, 1, size-sz, file);
			
			if(size == 0)
            {
			    if(sz > 0)
                {
                    len = Data_ToStringBuf(strbuf, mem, mem+sz-1);

                    Hex_ToStringBuf(strbuf+len+1, mem, mem+sz);

					printf("%08X ", filePos);
                    printf("%-32s ", strbuf+len+1);
                    printf("%s\n", strbuf);
                }
				
			    break;
            }

			lastPos = mem;
			size += sz;

            memset(mem+size, 0, 15);

			continue;
		}
		
		Hex_ToStringBuf(strbuf+len+1, prevPos, lastPos);

		printf("%08X ", filePos);
        printf("%-32s ", strbuf+len+1);
        printf("%s\n", strbuf);
		
		filePos += lastPos - prevPos;
    }

	fclose(file);

	return 0;
}