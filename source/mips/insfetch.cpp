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
	while( 1 )
	{
		while( cpu->pc() >= cpu->pcTop && !fwd->exit )
		{
			std::this_thread::yield();
			if( fwd->clear_if )
			{
				fwd->ok_if = 0;
				fwd->clear_if = 0;
			}
		}

		if( fwd->exit )
			break;

		if( mipsDebug::stepInformation )
		{
			mipsDebug::lock.lock();
			std::cerr << mipsDebug::nowLine( cpu->pc() ) << std::endl;
			mipsDebug::lock.unlock();
		}

		mif = run();

		if( mipsDebug::stepInformation_detail )
		{
			mipsDebug::lock.lock();
			std::cerr << "[IF]"
			<< mipsDebug::tostr(mif) << std::endl;
			mipsDebug::lock.unlock();
		}


		cpu->pc() += 12;
		while( fwd->ok_if )
		{
			std::this_thread::yield();
			if( fwd->clear_if )
			{
				fwd->ok_if = 0;
			}
		}
		fwd->mif = mif;
		fwd->ok_if = 1;



		//cpu->lock_pc0.lock();
		while( cpu->lock_pc0.try_lock() )
		{
			std::this_thread::yield();
			if( fwd->clear_if )
			{
				fwd->ok_if = 0;
				fwd->clear_if = 0;
			}
		}
		cpu->lock_pc0.unlock();

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
