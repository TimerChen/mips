#include "insfetch.h"

InsFetch::InsFetch( CPU *cpuAdress )
	:Device( cpuAdress )
{
}
MsgIF InsFetch::run( )
{
	lock();
	Instruction ins;
	MsgIF msg;
	char *re = msg.str;
	*((unsigned int*)(re + 0)) = cpu->read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	*((unsigned int*)(re + 0)) = cpu->read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	*((unsigned int*)(re + 0)) = cpu->read_mem( cpu->pc(), 4 );
	return msg;
}
