#include "insdecode.h"

#include "instruction.h"

InsDecode::InsDecode( CPU *cpuAdress )
	:Stage( cpuAdress )
{

}

bool InsDecode::isFree( const MsgIF &msgIF )
{
	Instruction ins;
	ins = *((Instruction*)(msgIF.str));
	if( ins.opt == Instruction::Inst::syscall )
	{
		//for syscall

		//read $v0
		if( !cpu->isFree( 2 ) )
			return 0;
		switch( cpu->read_reg( 2 ) )
		{
			case 8:
				//read $a1
				if( !cpu->isFree( 5 ) )
					return 0;
			case 1:case 4:case 9:case 17:
				//read $a0
				if( !cpu->isFree( 4 ) )
					return 0;
			break;
			case 5:case 10:
			break;
		}
	}else if( ins.opt == Instruction::Inst::mflo ){
		if( !cpu->isFree( 32 ) )
			return 0;
	}else if( ins.opt == Instruction::Inst::mfhi ){
		if( !cpu->isFree( 33 ) )
			return 0;
	}else if( ins.opt == Instruction::Inst::jal ){
		;
	}else if( ins.opt == Instruction::Inst::jalr ){
		;
	}else if( ins.opt == Instruction::Inst::jr ){
		if( !cpu->isFree( ins.arg0 ) )
			return 0;
	}else{
		if(ins.arg0 < 32)
		{
			if( (Instruction::Inst::beq <= ins.opt &&
				 ins.opt <= Instruction::Inst::bltz) ||
				(Instruction::Inst::sb <= ins.opt &&
				 ins.opt <= Instruction::Inst::sw) ||
				(Instruction::Inst::mul2 <= ins.opt &&
				 ins.opt <= Instruction::Inst::divu2) )
			{
				if( !cpu->isFree( ins.arg0 ) )
					return 0;
			}
		}
		if(ins.arg1 < 32)
		{
			if( !cpu->isFree( ins.arg1 ) )
				return 0;
		}
		if(ins.arg2 < 32)
		{
			if( !cpu->isFree( ins.arg2 ) )
				return 0;
		}
	}
	return 1;
}

MsgID InsDecode::run(const MsgIF &msgIF)
{
	MsgID msgID;
	Instruction ins;
	ins = *((Instruction*)(msgIF.str));
	msgID.opt = ins.opt;
	if( ins.opt == Instruction::Inst::syscall )
	{
		//for syscall

		//read $v0
		msgID.arg[0] = cpu->read_reg( 2 );
		msgID.narg = 1;
		switch( msgID.arg[0] )
		{
			case 8:
				//read $a1
				msgID.arg[2] = cpu->read_reg( 5 );
				msgID.narg++;
			case 1:case 4:case 9:case 17:
				//read $a0
				msgID.arg[1] = cpu->read_reg( 4 );
				msgID.narg++;
			break;
			case 5:case 10:
			break;
		}
	}else if( ins.opt == Instruction::Inst::mflo ){
		msgID.narg = 2;
		msgID.arg[0] = ins.arg0;
		msgID.arg[1] = cpu->read_reg(32);
	}else if( ins.opt == Instruction::Inst::mfhi ){
		msgID.narg = 1;
		msgID.arg[0] = ins.arg0;
		msgID.arg[1] = cpu->read_reg(33);
	}else if( ins.opt == Instruction::Inst::jal ){
		msgID.narg = 2;
		msgID.arg[0] = ins.arg3;
		//pc
		//msgID.arg[1] = cpu->read_reg(34);
		msgID.arg[1] = msgIF.add;
	}else if( ins.opt == Instruction::Inst::jalr ){
		msgID.narg = 2;
		msgID.arg[0] = cpu->read_reg(ins.arg0);
		//pc
		//msgID.arg[1] = cpu->read_reg(34);
		msgID.arg[1] = msgIF.add;
	}else if( ins.opt == Instruction::Inst::jr ){
		msgID.narg = 1;
		msgID.arg[0] = cpu->read_reg(ins.arg0);
	}else{
		msgID.narg = 0;
		if(ins.arg0 < 32)
		{
			if( (Instruction::Inst::beq <= ins.opt &&
				 ins.opt <= Instruction::Inst::bltz) ||
				(Instruction::Inst::sb <= ins.opt &&
				 ins.opt <= Instruction::Inst::sw) ||
				(Instruction::Inst::mul2 <= ins.opt &&
				 ins.opt <= Instruction::Inst::divu2) )
				msgID.arg[msgID.narg++] = cpu->read_reg(ins.arg0);
			else
				msgID.arg[msgID.narg++] = ins.arg0;
		}
		if(ins.arg1 < 32)
			msgID.arg[msgID.narg++] = cpu->read_reg(ins.arg1);
		if(ins.arg2 < 32)
			msgID.arg[msgID.narg++] = cpu->read_reg(ins.arg2);
		msgID.arg[msgID.narg++] = ins.arg3;
		msgID.arg[msgID.narg++] = ins.arg4;
	}

	//lock regs

	if( Instruction::Inst::syscall == ins.opt )
	{
		//$v0
		switch( msgID.arg[0] )
		{
			case 5:case 9:
				//lock $v0
				cpu->lockReg( 2 );
			break;
		}
	}else{
		if( (Instruction::Inst::add <= ins.opt &&
			 ins.opt <= Instruction::Inst::sne) ||
			(Instruction::Inst::la <= ins.opt &&
			ins.opt <= Instruction::Inst::lw) ||
			(Instruction::Inst::move <= ins.opt &&
			ins.opt <= Instruction::Inst::mflo) )
			cpu->lockReg( ins.arg0 );

		if(Instruction::Inst::b <= ins.opt &&
		   ins.opt <= Instruction::Inst::jalr)
			cpu->lockReg( 34 );
		if(Instruction::Inst::jal <= ins.opt &&
			ins.opt <= Instruction::Inst::jalr)
			cpu->lockReg( 31 );

		if( Instruction::Inst::mul2 <= ins.opt &&
			ins.opt <= Instruction::Inst::divu2 )
			cpu->lockReg( 32 ), cpu->lockReg( 33 );
	}


	return msgID;
}
