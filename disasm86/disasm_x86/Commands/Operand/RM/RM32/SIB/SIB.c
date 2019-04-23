#include <string.h>
#include "SIB.h"

int SIB_ToStringBuf(char* buf, SIB sib, Mod mod, union ImmValue rmDisp)
{
	char* startBuf = buf;
	
	*buf = '[';
	buf++;
	buf += Index_ToStringBuf(buf, sib.index, sib.ss);
	
	if(buf != startBuf+1)
	{
		*buf = '+';
		buf++;
	}
	
	buf += Base_ToStringBuf(buf, sib.base, mod, rmDisp);
	strcpy(buf, "]");
	buf++;
	
	return buf - startBuf;
}