#include "execute.h"

Execute::Execute( CPU* cpuAdress )
	:Device( cpuAdress )
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
			msgEX.arg[0] = msgID.arg[0];
			tmp = (Data)msgID.arg[1] * (Data)msgID.arg[2];
			//hi
			msgEX.arg[1] = *((Data*)(&tmp));
			//lo
			msgEX.arg[0] = *((Data*)(&tmp+4));
		}break;

		case Instruction::Inst::mulu2:
		{
			typedef unsigned int Data;
			unsigned long long tmp;
			msgEX.opt = MsgEX::msgType::r2lh;
			msgEX.arg[0] = msgID.arg[0];
			tmp = (Data)msgID.arg[1] * (Data)msgID.arg[2];
			//hi
			msgEX.arg[1] = *((Data*)(&tmp));
			//lo
			msgEX.arg[0] = *((Data*)(&tmp+4));
		}break;

		case Instruction::Inst::div2:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r2lh;
			msgEX.arg[0] = msgID.arg[0];
			//lo
			*((Data*)(&msgEX.arg[0])) = (Data)msgID.arg[1] / (Data)msgID.arg[2];
			//hi
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] % (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::divu2:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r2lh;
			msgEX.arg[0] = msgID.arg[0];
			//lo
			*((Data*)(&msgEX.arg[0])) = (Data)msgID.arg[1] / (Data)msgID.arg[2];
			//hi
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] % (Data)msgID.arg[2];
		}break;
		case Instruction::Inst::xor0:
		{
			typedef int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] xor (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::xoru:
		{
			typedef unsigned int Data;
			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] xor (Data)msgID.arg[2];
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
			if( msgID.arg[1] == msgID.arg[2] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bne:
		{
			if( msgID.arg[1] != msgID.arg[2] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bge:
		{
			if( msgID.arg[1] >= msgID.arg[2] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::ble:
		{
			if( msgID.arg[1] <= msgID.arg[2] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bgt:
		{
			if( msgID.arg[1] > msgID.arg[2] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::blt:
		{
			if( msgID.arg[1] < msgID.arg[2] )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::beqz:
		{
			if( msgID.arg[1] == 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bnez:
		{
			if( msgID.arg[1] != 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bgez:
		{
			if( msgID.arg[1] >= 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::blez:
		{
			if( msgID.arg[1] <= 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bgtz:
		{
			if( msgID.arg[1] > 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
			}else{
				msgEX.opt = MsgEX::msgType::non;
			}
		}break;

		case Instruction::Inst::bltz:
		{
			if( msgID.arg[1] < 0 )
			{
				msgEX.opt = MsgEX::msgType::r1;
				msgEX.arg[0] = 34;
				msgEX.arg[1] = msgID.arg[0];
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
			if( msgID.narg == 2 )
				//reg label
				msgEX.arg[1] = msgID.arg[1];
			else
				//address + offset
				msgEX.arg[1] = msgID.arg[1] + msgID.arg[2];
		}break;
		case Instruction::Inst::sb:
		case Instruction::Inst::sh:
		case Instruction::Inst::sw:
		{
			msgEX.opt = MsgEX::msgType::store;
			msgEX.arg[0] = msgID.arg[0];
			if( msgID.narg == 2 )
				//reg label
				msgEX.arg[1] = msgID.arg[1];
			else
				//address + offset
				msgEX.arg[1] = msgID.arg[1] + msgID.arg[2];
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

		}break;





	}
	return msgEX;
}
