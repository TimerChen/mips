#include "execute.h"

Execute::Execute( CPU* cpuAdress )
	:Stage( cpuAdress )
{

}
MsgEX Execute::run( const MsgID &msgID )
{
	MsgEX msgEX;
	switch( msgID.opt )
	{

		case Instruction::Inst::add:
		case Instruction::Inst::addu:
		case Instruction::Inst::addiu:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = msgID.arg[1] + msgID.arg[2];
		}break;

		case Instruction::Inst::sub:
		case Instruction::Inst::subu:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = msgID.arg[1] - msgID.arg[2];
		}break;
		case Instruction::Inst::mul:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] * (Data)msgID.arg[2];
		}break;
		case Instruction::Inst::mulu:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] * (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::div:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] / (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::divu:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] / (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::mul2:
		{
			typedef int Data;
			long long tmp;
			msgEX.opt = MsgEX::msgType::r2lh;
			tmp = (long long)((Data)msgID.arg[0]) * (Data)msgID.arg[1];
			//hi
			msgEX.arg[1] = *((Data*)(&tmp+4));
			//lo
			msgEX.arg[0] = *((Data*)(&tmp));
		}break;

		case Instruction::Inst::mulu2:
		{
			typedef unsigned int Data;
			unsigned long long tmp;
			msgEX.opt = MsgEX::msgType::r2lh;
			tmp = (unsigned long long)((Data)msgID.arg[0]) * (Data)msgID.arg[1];
			//hi
			msgEX.arg[1] = *((Data*)(&tmp+4));
			//lo
			msgEX.arg[0] = *((Data*)(&tmp));
		}break;

		case Instruction::Inst::div2:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r2lh;
			//lo
			*((Data*)(&msgEX.arg[0])) = (Data)msgID.arg[0] / (Data)msgID.arg[1];
			//hi
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[0] % (Data)msgID.arg[1];
		}break;

		case Instruction::Inst::divu2:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r2lh;
			//lo
			*((Data*)(&msgEX.arg[0])) = (Data)msgID.arg[0] / (Data)msgID.arg[1];
			//hi
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[0] % (Data)msgID.arg[1];
		}break;
		case Instruction::Inst::xor0:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] ^ (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::xoru:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] ^ (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::neg:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = -(Data)msgID.arg[1];
		}break;

		case Instruction::Inst::negu:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = -(Data)msgID.arg[1];
		}break;

		case Instruction::Inst::rem:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] % (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::remu:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] % (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::li:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1];
		}break;

		case Instruction::Inst::seq:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = ( (Data)msgID.arg[1] == (Data)msgID.arg[2] );
		}break;

		case Instruction::Inst::sge:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = ( (Data)msgID.arg[1] >= (Data)msgID.arg[2] );
		}break;

		case Instruction::Inst::sgt:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = ( (Data)msgID.arg[1] > (Data)msgID.arg[2] );
		}break;

		case Instruction::Inst::sle:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = ( (Data)msgID.arg[1] <= (Data)msgID.arg[2] );
		}break;

		case Instruction::Inst::slt:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = ( (Data)msgID.arg[1] < (Data)msgID.arg[2] );
		}break;

		case Instruction::Inst::sne:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = ( (Data)msgID.arg[1] != (Data)msgID.arg[2] );
		}break;

		case Instruction::Inst::b:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = 34;
			msgEX.arg[1] = msgID.arg[0];
		}break;

		case Instruction::Inst::beq:
		{
			if( msgID.arg[0] == msgID.arg[1] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[2];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bne:
		{
			if( msgID.arg[0] != msgID.arg[1] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[2];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bge:
		{
			if( msgID.arg[0] >= msgID.arg[1] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[2];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::ble:
		{
			if( msgID.arg[0] <= msgID.arg[1] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[2];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bgt:
		{
			if( msgID.arg[0] > msgID.arg[1] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[2];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::blt:
		{
			if( msgID.arg[0] < msgID.arg[1] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[2];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::beqz:
		{
			if( msgID.arg[0] == 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[1];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bnez:
		{
			if( msgID.arg[0] != 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[1];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bgez:
		{
			if( msgID.arg[0] >= 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[1];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::blez:
		{
			if( msgID.arg[0] <= 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[1];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bgtz:
		{
			if( msgID.arg[0] > 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[1];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bltz:
		{
			if( msgID.arg[0] < 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[1];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::j:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = 34;
			msgEX.arg[1] = msgID.arg[0];
		}break;

		case Instruction::Inst::jr:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = 34;
			msgEX.arg[1] = msgID.arg[0];
		}break;

		case Instruction::Inst::jal:
		{
			msgEX.opt = MsgEX::msgType::r2j;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = msgID.arg[1];
		}break;

		case Instruction::Inst::jalr:
		{
			msgEX.opt = MsgEX::msgType::r2j;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = msgID.arg[1];
		}break;

		case Instruction::Inst::la:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = msgID.arg[1];
		}break;

		case Instruction::Inst::lb:
		case Instruction::Inst::lh:
		case Instruction::Inst::lw:
		{
			msgEX.opt = MsgEX::msgType::load;
			msgEX.arg[0] = msgID.arg[0];
			if( msgID.narg == 3 )
				//reg label
				msgEX.arg[1] = msgID.arg[1];
			else
				//address + offset
				msgEX.arg[1] = msgID.arg[1] + msgID.arg[2];
			if( msgID.opt == Instruction::Inst::lb )
				msgEX.arg[2] = 1;
			else if( msgID.opt == Instruction::Inst::lh )
				msgEX.arg[2] = 2;
			else if( msgID.opt == Instruction::Inst::lw )
				msgEX.arg[2] = 4;
		}break;
		case Instruction::Inst::sb:
		case Instruction::Inst::sh:
		case Instruction::Inst::sw:
		{
			msgEX.opt = MsgEX::msgType::store;
			msgEX.arg[0] = msgID.arg[0];
			if( msgID.narg == 3 )
				//reg label
				msgEX.arg[1] = msgID.arg[1];
			else
				//address + offset
				msgEX.arg[1] = msgID.arg[1] + msgID.arg[2];
			if( msgID.opt == Instruction::Inst::sb )
				msgEX.arg[2] = 1;
			else if( msgID.opt == Instruction::Inst::sh )
				msgEX.arg[2] = 2;
			else if( msgID.opt == Instruction::Inst::sw )
				msgEX.arg[2] = 4;
		}break;

		case Instruction::Inst::move:
		case Instruction::Inst::mfhi:
		case Instruction::Inst::mflo:
		{
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = msgID.arg[1];
		}break;
		case Instruction::Inst::nop:
		{

		}break;

		case Instruction::Inst::syscall:
		{
			switch (msgID.arg[0]) {
			case 1:
				msgEX.opt = MsgEX::msgType::oInt;
				msgEX.arg[0] = msgID.arg[1];
				break;
			case 4:
				msgEX.opt = MsgEX::msgType::oStr;
				msgEX.arg[0] = msgID.arg[1];
				break;
			case 5:
				msgEX.opt = MsgEX::msgType::iInt;
				break;
			case 8:
				msgEX.opt = MsgEX::msgType::iStr;
				msgEX.arg[0] = msgID.arg[1];
				msgEX.arg[1] = msgID.arg[2];
				break;
			case 9:
				msgEX.opt = MsgEX::msgType::space;
				msgEX.arg[0] = msgID.arg[1];
				break;
			case 10:
				msgEX.opt = MsgEX::msgType::exit;
				break;
			case 17:
				msgEX.opt = MsgEX::msgType::exit0;
				msgEX.arg[0] = msgID.arg[1];
				break;
			}
		}break;

	}



	return msgEX;
}
