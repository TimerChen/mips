#include "writeback.h"

#include "debug.h"

#include <thread>

WriteBack::WriteBack( CPU *cpuAdress, Forwarder *forwarder )
	:Stage( cpuAdress, forwarder )
{

}
void WriteBack::work()
{
	MsgMEM mmem;
	MsgWB mwb;
	while( !fwd->exit )
	{
		//Data-hazard lock(lock-free)
		//
		while( !fwd->ok_mem && !fwd->exit )
			std::this_thread::yield();
		mmem = fwd->mmem;
		fwd->ok_mem = 0;

		//run
		mwb = run( mmem );

		//debug
		if( mipsDebug::stepInformation_detail )
		{
			mipsDebug::lock.lock();
			std::cerr <<  "[WB]"
			<< mipsDebug::tostr(mwb) << std::endl;
			mipsDebug::lock.unlock();
		}

		//ready to exit...
		if( mwb.opt != MsgWB::msgType::non )
			break;
	}
	fwd->exit = 1;
	fwd->mwb = mwb;
}

MsgWB WriteBack::run( const MsgMEM &msgMEM )
{
	MsgWB msgWB;
	msgWB.opt = MsgWB::msgType::non;
	switch ( msgMEM.opt ) {
	case MsgMEM::msgType::non:
		//non
		break;
	case MsgMEM::msgType::r1:
		//non
		cpu->write_reg( msgMEM.arg[0], msgMEM.arg[1] );
		break;
	case MsgMEM::msgType::r2lh:
		//non
		cpu->write_reg( 32, msgMEM.arg[0] );
		cpu->write_reg( 33, msgMEM.arg[1] );
		break;
	case MsgMEM::msgType::r2j:
		//non
		cpu->write_reg( 34, msgMEM.arg[0] );
		cpu->write_reg( 31, msgMEM.arg[1] );
		break;
	case MsgMEM::msgType::exit:
		msgWB.opt = MsgWB::msgType::exit;
		break;
	case MsgMEM::msgType::exit0:
		msgWB.opt = MsgWB::msgType::exit0;
		msgWB.arg = msgMEM.arg[0];
		break;
	}
	if( ( msgMEM.opt == MsgMEM::msgType::r1 && msgMEM.arg[0] == 34 ) ||
		msgMEM.opt == MsgMEM::msgType::r2j )
	{
		//wait for clear line
		cpu->lock_pc0.lock();
		cpu->lock_pc1.lock();

		fwd->clear_ifline = fwd->clear_idline = 1;
		fwd->clear_if = fwd->clear_id = 0;

		cpu->lock_pc0.unlock();
		cpu->lock_pc1.unlock();
	}
	return msgWB;
}
