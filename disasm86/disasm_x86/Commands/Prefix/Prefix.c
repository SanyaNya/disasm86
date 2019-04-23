#include <string.h>
#include "Prefix.h"

const char* Prefix_ToString(Prefix prefix)
{
    switch (prefix)
    {
        case PREFIX_OVERRIDE_ES: return "es:";
        case PREFIX_OVERRIDE_CS: return "cs:";
        case PREFIX_OVERRIDE_SS: return "ss:";
        case PREFIX_OVERRIDE_DS: return "ds:";
        case PREFIX_OVERRIDE_FS: return "fs:";
        case PREFIX_OVERRIDE_GS: return "gs:";

        //Не требуются, так как по операндам понятен размер
        case PREFIX_OVERRIDE_OPERAND_SIZE: return "";
        case PREFIX_OVERRIDE_ADDR_SIZE:    return "";

        case PREFIX_WAIT:  return "wait";
        case PREFIX_LOCK:  return "lock";
        case PREFIX_REPNZ: return "repnz";
        case PREFIX_REPZ:  return "repz";
    
        default: return "";
    }
}

int Prefix_ToStringBuf(char* buf, Prefix prefix)
{
	strcpy(buf, Prefix_ToString(prefix));
	return strlen(buf);
}

static int IsStrOp(int prefix_0f, uint8_t op)
{
	return !prefix_0f &&
		   (
		    op == 0x6c  ||
			op == 0x6d  ||
		    op == 0x6e  ||
			op == 0x6f  ||
		    op == 0xa4  ||
			op == 0xa5  ||
			op == 0xa6  ||
			op == 0xa7  ||
		    op == 0xaa  ||
			op == 0xab  ||
			op == 0xac  ||
			op == 0xad  ||
		    op == 0xae  ||
			op == 0xaf
			);
}

static void FixPrefixes(Prefixes* pprefixes, const uint8_t* cmd, Proc proc, int mayHaveLock)
{
	Prefix prefixWaitLockRep = pprefixes->prefix_waitLockRep;
	Prefix prefixSeg = pprefixes->prefix_seg;
	
	if((!IsStrOp(pprefixes->prefix_0f == PREFIX_0F, *cmd) && (prefixWaitLockRep == PREFIX_REPZ || prefixWaitLockRep == PREFIX_REPNZ)) ||
	  (!mayHaveLock && prefixWaitLockRep == PREFIX_LOCK))
		pprefixes->prefix_waitLockRep = PREFIX_NONE;
					
	if(!Procs_CompatibleWith(proc, PROC_AFTER_03) && (prefixSeg == PREFIX_OVERRIDE_FS || prefixSeg == PREFIX_OVERRIDE_GS))
		pprefixes->prefix_seg = PREFIX_NONE;
}

const uint8_t* GetPrefixes(Prefixes* pprefixes, const uint8_t* cmd, Proc proc, int mayHaveLock)
{
	pprefixes->prefix_0f          = PREFIX_NONE;
	pprefixes->prefix_seg         = PREFIX_NONE;
	pprefixes->prefix_opsize      = PREFIX_NONE;
	pprefixes->prefix_addrsize    = PREFIX_NONE;
	pprefixes->prefix_waitLockRep = PREFIX_NONE;
	
	for(uint8_t byte = *cmd; ; byte = *(++cmd))
	{
		switch(byte)
		{
			case PREFIX_0F:
				if(pprefixes->prefix_0f == PREFIX_NONE)
					pprefixes->prefix_0f = byte;

				cmd++;
                FixPrefixes(pprefixes, cmd, proc, mayHaveLock);
                return cmd;
			
			case PREFIX_OVERRIDE_ES:
			case PREFIX_OVERRIDE_CS:
			case PREFIX_OVERRIDE_SS:
			case PREFIX_OVERRIDE_DS:
			case PREFIX_OVERRIDE_FS:
			case PREFIX_OVERRIDE_GS:
				if(pprefixes->prefix_seg == PREFIX_NONE)
					pprefixes->prefix_seg = byte;
				break;
			
			case PREFIX_OVERRIDE_OPERAND_SIZE:
				if(pprefixes->prefix_opsize == PREFIX_NONE)
					pprefixes->prefix_opsize = byte;
				break;
			
			case PREFIX_OVERRIDE_ADDR_SIZE:
				if(pprefixes->prefix_addrsize == PREFIX_NONE)
					pprefixes->prefix_addrsize = byte;
				break;
			
			case PREFIX_WAIT:
			case PREFIX_LOCK:
			case PREFIX_REPNZ:
			case PREFIX_REPZ:
				if(pprefixes->prefix_waitLockRep == PREFIX_NONE)
					pprefixes->prefix_waitLockRep = byte;
				break;
				
			default:
				FixPrefixes(pprefixes, cmd, proc, mayHaveLock);
				return cmd;
		}
	}
}

Prefix GetPrefix(CompressedPrefix p)
{
	switch(p)
	{
		case CMPRSD_PREFIX_NONE:                    return PREFIX_NONE;
		case CMPRSD_PREFIX_0F:                      return PREFIX_0F;
		case CMPRSD_PREFIX_OVERRIDE_ES:             return PREFIX_OVERRIDE_ES;
		case CMPRSD_PREFIX_OVERRIDE_CS:             return PREFIX_OVERRIDE_CS;
		case CMPRSD_PREFIX_OVERRIDE_SS:             return PREFIX_OVERRIDE_SS;
		case CMPRSD_PREFIX_OVERRIDE_DS:             return PREFIX_OVERRIDE_DS;
		case CMPRSD_PREFIX_OVERRIDE_FS:             return PREFIX_OVERRIDE_FS;
		case CMPRSD_PREFIX_OVERRIDE_GS:             return PREFIX_OVERRIDE_GS;
		case CMPRSD_PREFIX_OVERRIDE_OPERAND_SIZE:   return PREFIX_OVERRIDE_OPERAND_SIZE;
		case CMPRSD_PREFIX_OVERRIDE_ADDR_SIZE:      return PREFIX_OVERRIDE_ADDR_SIZE;
		case CMPRSD_PREFIX_WAIT:                    return PREFIX_WAIT;
		case CMPRSD_PREFIX_LOCK:	                return PREFIX_LOCK;
		case CMPRSD_PREFIX_REPNZ:                   return PREFIX_REPNZ;
		case CMPRSD_PREFIX_REPZ:                    return PREFIX_REPZ;
		
		default: return PREFIX_NONE;
	}
}