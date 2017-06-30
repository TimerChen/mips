#include "writeback.h"

WriteBack::WriteBack( CPU *cpuAdress )
	:Device( cpuAdress )
{

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
