#include "insfetch.h"

#include "error.h"

InsFetch::InsFetch( CPU *cpuAdress )
	:Stage( cpuAdress )
{
}
bool InsFetch::isFree()
{
	return cpu->isFree_pc();
}

MsgIF InsFetch::run( )
{
	if( !cpu->isFree_pc() )
		throw( StageLocked() );

	Instruction ins;
	MsgIF msg;
	char *re = msg.str;
	*((unsigned int*)(re + 0)) = cpu->read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	*((unsigned int*)(re + 4)) = cpu->read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	*((unsigned int*)(re + 8)) = cpu->read_mem( cpu->pc(), 4 );
	cpu->pc() += 4;
	msg.add = cpu->pc();
	return msg;
}
