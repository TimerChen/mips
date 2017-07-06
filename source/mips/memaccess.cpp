#include "memaccess.h"

#include "debug.h"

#include <thread>

MemAccess::MemAccess( CPU* cpuAdress, Forwarder *forwarder )
	:Stage( cpuAdress, forwarder )
{

}
void MemAccess::work()
{
	MsgEX mex;
	MsgMEM mmem;
	while( !fwd->exit )
	{
		//Data-hazard lock(lock-free)
		//
		while( !fwd->ok_ex && !fwd->exit )
			std::this_thread::yield();
		mex = fwd->mex;
		fwd->ok_ex = 0;

		//run
		mmem = run( mex );

		//debug
		if( mipsDebug::stepInformation_detail )
		{
			mipsDebug::lock.lock();
			std::cerr << "[MA]"
			<< mipsDebug::tostr(mmem) << std::endl;
			mipsDebug::lock.unlock();
		}

		//Control-hazard lock
		while( fwd->ok_mem && !fwd->exit ){
			std::this_thread::yield();
		}
		fwd->mmem = mmem;
		fwd->ok_mem = 1;
	}
}

MsgMEM MemAccess::run( const MsgEX &msgEX )
{
	MsgMEM msgMEM;
	msgMEM.opt = MsgMEM::msgType::non;
	switch( msgEX.opt )
	{
	case MsgEX::msgType::non:
		//non
		break;
	case MsgEX::msgType::r1:
		msgMEM.opt = MsgMEM::msgType::r1;
		msgMEM.arg[0] = msgEX.arg[0];
		msgMEM.arg[1] = msgEX.arg[1];
		break;
	case MsgEX::msgType::r2lh:
		msgMEM.opt = MsgMEM::msgType::r2lh;
		msgMEM.arg[0] = msgEX.arg[0];
		msgMEM.arg[1] = msgEX.arg[1];
//		cpu->write_reg( 32, msgEX.arg[0] );
//		cpu->write_reg( 33, msgEX.arg[1] );
		break;
	case MsgEX::msgType::r2j:
		msgMEM.opt = MsgMEM::msgType::r2j;
		msgMEM.arg[0] = msgEX.arg[0];
		msgMEM.arg[1] = msgEX.arg[1];
//		cpu->write_reg( 34, msgEX.arg[0] );
//		cpu->write_reg( 31, msgEX.arg[1] );
		break;
	case MsgEX::msgType::load:
		msgMEM.opt = MsgMEM::msgType::r1;
		msgMEM.arg[0] = msgEX.arg[0];
		msgMEM.arg[1] =	cpu->read_mem( msgEX.arg[1], msgEX.arg[2] );
		break;
	case MsgEX::msgType::store:
		//non
		cpu->write_mem( msgEX.arg[1], msgEX.arg[0], msgEX.arg[2] );
		break;
	case MsgEX::msgType::oInt:
		//non
		cpu->write_ioInt( msgEX.arg[0] );
		break;
	case MsgEX::msgType::oStr:
		//non
	{
		std::string str;
		str = cpu->read_memStr( msgEX.arg[0] );
		cpu->write_ioStr( str );
	}
		break;
	case MsgEX::msgType::iInt:
		msgMEM.opt = MsgMEM::msgType::r1;
		msgMEM.arg[0] = 2;
		msgMEM.arg[1] = cpu->read_ioInt();
		break;
	case MsgEX::msgType::iStr:
		//non
		cpu->read_ioStr( msgEX.arg[0], msgEX.arg[1] );
		break;
	case MsgEX::msgType::space:
		//non
		msgMEM.opt = MsgMEM::msgType::r1;
		msgMEM.arg[0] = 2;
		msgMEM.arg[1] = cpu->ptop();
		cpu->ptop() = cpu->newSpace( msgEX.arg[0] );
		break;
	case MsgEX::msgType::exit:
		msgMEM.opt = MsgMEM::msgType::exit;
		break;
	case MsgEX::msgType::exit0:
		msgMEM.opt = MsgMEM::msgType::exit0;
		msgMEM.arg[0] = msgEX.arg[0];
		break;
	}

	return msgMEM;
}
