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
	while( 1 )
	{
		//Data-hazard lock(lock-free)
		//
		while( !fwd->ok_mem )
			std::this_thread::yield();
		mmem = fwd->mmem;
		fwd->ok_mem = 0;

		//run
		mwb = run( mmem );

		//debug
		if( mipsDebug::stepInformation_detail )
			//cerr << "done\n" << "Write Back:\n";
			std::cerr << mipsDebug::tostr(mwb) << std::endl;

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
	return msgWB;
}
