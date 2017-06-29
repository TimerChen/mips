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
			*((Data*)(&msgEX.arg[1])) = (Data)msgID.arg[1] * (Data)msgID.arg[2];
		}break;

		case Instruction::Inst::divu:
		{

			msgEX.opt = MsgEX::msgType::r1;
			msgEX.arg[0] = msgID.arg[0];
			msgEX.arg[1] = (unsigned int)msgID.arg[1] / (unsigned int)msgID.arg[2];
		}break;

		case Instruction::Inst::mul2:
		{
		}break;

		case Instruction::Inst::mulu2:
		{
		}break;

		case Instruction::Inst::div2:
		{
		}break;

		case Instruction::Inst::divu2:
		{
		}break;
		case Instruction::Inst::xor0:
		{
		}break;

		case Instruction::Inst::xoru:
		{
		}break;

		case Instruction::Inst::neg:
		{
		}break;

		case Instruction::Inst::negu:
		{
		}break;

		case Instruction::Inst::rem:
		{
		}break;

		case Instruction::Inst::remu:
		{
		}break;

		case Instruction::Inst::li:
		{
		}break;

		case Instruction::Inst::seq:
		{
		}break;

		case Instruction::Inst::sge:
		{
		}break;

		case Instruction::Inst::sgt:
		{
		}break;

		case Instruction::Inst::sle:
		{
		}break;

		case Instruction::Inst::slt:
		{
		}break;

		case Instruction::Inst::sne:
		{
		}break;

		case Instruction::Inst::b:
		{
		}break;

		case Instruction::Inst::beq:
		{
		}break;

		case Instruction::Inst::bne:
		{
		}break;

		case Instruction::Inst::bge:
		{
		}break;

		case Instruction::Inst::ble:
		{
		}break;

		case Instruction::Inst::bgt:
		{
		}break;

		case Instruction::Inst::blt:
		{
		}break;

		case Instruction::Inst::beqz:
		{
		}break;

		case Instruction::Inst::bnez:
		{
		}break;

		case Instruction::Inst::blez:
		{
		}break;

		case Instruction::Inst::bgez:
		{
		}break;

		case Instruction::Inst::bgtz:
		{
		}break;

		case Instruction::Inst::bltz:
		{
		}break;

		case Instruction::Inst::j:
		{
		}break;

		case Instruction::Inst::jr:
		{
		}break;

		case Instruction::Inst::jal:
		{
		}break;

		case Instruction::Inst::jalr:
		{
		}break;

		case Instruction::Inst::la:
		{
		}break;

		case Instruction::Inst::lb:
		{
		}break;

		case Instruction::Inst::lh:
		{
		}break;

		case Instruction::Inst::lw:
		{
		}break;

		case Instruction::Inst::sb:
		{
		}break;

		case Instruction::Inst::sh:
		{
		}break;

		case Instruction::Inst::sw:
		{
		}break;

		case Instruction::Inst::move:
		{
		}break;

		case Instruction::Inst::mfhi:
		{
		}break;

		case Instruction::Inst::mflo:
		{
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
