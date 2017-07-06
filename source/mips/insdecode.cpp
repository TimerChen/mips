#include "insdecode.h"

#include "instruction.h"
#include "debug.h"

#include <thread>

InsDecode::InsDecode( CPU *cpuAdress, Forwarder *forwarder )
	:Stage( cpuAdress, forwarder )
{

}
void InsDecode::work()
{
	MsgIF mif;
	MsgID mid;
	bool &ready = fwd->ready_id;
	ready = 0;
	while( 1 )
	{
		if( fwd->exit )
			break;

		if( !ready )
		{
			if( !fwd->ok_if )
			{
				std::this_thread::yield();
			}else{
				mif = fwd->mif;
				fwd->ok_if = 0;

				//run
				mid = run( mif );
				ready = 1;

				//debug
				if( mipsDebug::stepInformation_detail )
				{
					mipsDebug::lock.lock();
					std::cerr << "[ID]"
					<< mipsDebug::tostr(mid) << std::endl;
					mipsDebug::lock.unlock();
				}
			}
		}
		if( ready || fwd->clear_idline )
		{
			while( !fwd->exit )
			{
				if( cpu->lock_pc1.try_lock() )
				{
					std::this_thread::yield();
				}else{
					if( !fwd->clear_idline && !fwd->clear_id ){
						if( !fwd->ok_id && ready )
						{
							fwd->mid = mid;
							fwd->ok_id = 1;
							ready = 0;
							cpu->lock_pc1.unlock();
							break;
						}else
						{
							cpu->lock_pc1.unlock();
							break;
						}
					}else if( fwd->clear_idline ){
						cpu->clearLockReg();
						fwd->clear_idline = 0;
						ready = 0;
						if( !fwd->clear_id )
						{
							cpu->lock_pc1.unlock();
							break;
						}
					}
					cpu->lock_pc1.unlock();
				}
				std::this_thread::yield();
			}
		}
	}
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
				cpu->write_reg_ready( 2 );
				//cpu->lock[2].lock();
				//cpu->lockReg( 2 );
			break;
		}
	}else{
		//cpu->lock_pc1.lock();
		if( !fwd->clear_id )
		{
			if( (Instruction::Inst::add <= ins.opt &&
				 ins.opt <= Instruction::Inst::sne) ||
				(Instruction::Inst::la <= ins.opt &&
				ins.opt <= Instruction::Inst::lw) ||
				(Instruction::Inst::move <= ins.opt &&
				ins.opt <= Instruction::Inst::mflo) )
			{
				if(ins.arg0 != 34)
					cpu->write_reg_ready( ins.arg0 );
					//cpu->lock[ ins.arg0 ].lock();
				//cpu->lockReg( ins.arg0 );
			}
			/*
			if(Instruction::Inst::b <= ins.opt &&
			   ins.opt <= Instruction::Inst::jalr)
				cpu->lockReg( 34 );*/
			if(Instruction::Inst::jal <= ins.opt &&
				ins.opt <= Instruction::Inst::jalr)
				cpu->write_reg_ready( 31 );
				//cpu->lock[31].lock();
				//cpu->lockReg( 31 );

			if( Instruction::Inst::mul2 <= ins.opt &&
				ins.opt <= Instruction::Inst::divu2 )
			{
				cpu->write_reg_ready(32);
				cpu->write_reg_ready(33);
				//cpu->lock[32].lock();
				//cpu->lock[33].lock();
				//cpu->lockReg( 32 ), cpu->lockReg( 33 );
			}
		}
		//cpu->lock_pc1.unlock();
	}


	return msgID;
}
