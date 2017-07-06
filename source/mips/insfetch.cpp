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
	bool &ready = fwd->ready_if;
	ready = 0;
	while( 1 )
	{
		if( fwd->exit )
			break;
		if( !ready )
		{
			if( cpu->pc() >= cpu->pcTop )
			{
				std::this_thread::yield();
			}else{
				mif = run();
				//debug
				if( mipsDebug::stepInformation_detail )
				{
					mipsDebug::lock.lock();
					std::cerr << "Now Line: " << mipsDebug::nowLine(cpu->pc()) << std::endl
							  << "[IF]"
					<< mipsDebug::tostr(mif) << std::endl;
					mipsDebug::lock.unlock();
				}
				ready = 1;
			}
		}
		if( ready ){
			while( !fwd->exit )
			{
				if( cpu->lock_pc0.try_lock() )
				{
					std::this_thread::yield();
				}else{
					if( !fwd->clear_ifline && !fwd->clear_if ){
						if( !fwd->ok_if )
						{
							while ( fwd->clear_idline && !fwd->exit )
								std::this_thread::yield();

							if( mipsDebug::stepInformation_detail )
							{
								mipsDebug::lock.lock();
								std::cerr
										  << "[IF]"
								<< "msg out" << std::endl;
								mipsDebug::lock.unlock();
							}
							cpu->pc() += 12;
							fwd->mif = mif;
							fwd->ok_if = 1;
							ready = 0;

							cpu->lock_pc0.unlock();
							break;
						}
					}else if( fwd->clear_ifline ){
						fwd->clear_ifline = 0;
						ready = 0;
						if( !fwd->clear_if )
						{
							cpu->lock_pc0.unlock();
							break;
						}
					}
					cpu->lock_pc0.unlock();
				}
				std::this_thread::yield();
			}
		}
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
