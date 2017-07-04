#include "insfetch.h"

#include "error.h"
#include "debug.h"

#include <thread>

InsFetch::InsFetch( CPU *cpuAdress, Forwarder *forwarder )
	:Stage( cpuAdress, forwarder )
{

}

void InsFetch::work()
{
	MsgIF mif;
	while( !fwd->exit )
	{

		if( mipsDebug::stepInformation )
			std::cerr << mipsDebug::nowLine( cpu->pc() ) << std::endl;

		mif = run();

		if( mipsDebug::stepInformation_detail )
			//cerr << "Instruction Fetch:\n";
			std::cerr << mipsDebug::tostr(mif) << std::endl;

		cpu->lock_pc.lock();
		if( fwd->clear_if )
		{
			fwd->clear_if = 0;
		}else{
			cpu->pc() += 12;
			while( fwd->ok_if )
				std::this_thread::yield();
			fwd->mif = mif;
			fwd->ok_if = 1;
		}
		cpu->lock_pc.unlock();
	}
}

MsgIF InsFetch::run( )
{
//	if( !cpu->isFree_pc() )
//		throw( StageLocked() );
	Instruction ins;
	MsgIF msg;
	char *re = msg.str;

	//this maybe undefined behavior, but will never lead to a error
	msg.add = cpu->pc();

	*((unsigned int*)(re + 0)) = cpu->read_mem( msg.add + 0, 4 );
	*((unsigned int*)(re + 4)) = cpu->read_mem( msg.add + 4, 4 );
	*((unsigned int*)(re + 8)) = cpu->read_mem( msg.add + 8, 4 );

	msg.add += 12;
	return msg;
}
