#include "insfetch.h"

InsFetch::InsFetch( CPU *cpuAdress )
	:cpu(cpuAdress), Device()
{
}
Msg0 InsFetch::getIns( )
{
	lock();
	Instruction ins;
	Msg0 msg;
	char *re = msg.str;
	*((unsigned int*)(re + 0)) = read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	*((unsigned int*)(re + 0)) = read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	*((unsigned int*)(re + 0)) = read_mem( cpu->pc(), 4 );
	return msg;
}
