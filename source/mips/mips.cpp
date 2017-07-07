#include "mips.h"

#include "debug.h"

Mips::Mips(unsigned int MEMSIZE)
	:cpu(MEMSIZE),insInput(&cpu),
	  insFetch(&cpu), insDecode(&cpu), execute(&cpu),
	  memAceess(&cpu), writeBack(&cpu)
{
	ifFull = idFull = exFull = memFull = wbFull = 0;
}

Mips::~Mips()
{

}


void Mips::store( const MsgIF &msg )
{
	if( ifFull )
		throw( 0 );
	msgif = msg;
	ifFull = 1;
}

void Mips::store( const MsgID &msg )
{
	if( idFull )
		throw( 0 );
	msgid = msg;
	idFull = 1;
}

void Mips::store( const MsgEX &msg )
{
	if( exFull )
		throw( 0 );
	msgex = msg;
	exFull = 1;
}

void Mips::store( const MsgMEM &msg )
{
	if( memFull )
		throw( 0 );
	msgmem = msg;
	memFull = 1;
}

void Mips::store( const MsgWB &msg )
{
	if( wbFull )
		throw( 0 );
	msgwb = msg;
	wbFull = 1;
}

void Mips::clearLine()
{
	if( mipsDebug::lockInformation )
		std::cerr << "< clear line >" << std::endl;
	//clear msg
	ifFull = idFull = 0;
	//unlock regs
	cpu.clearLockReg();
}

bool Mips::lock_pc( const MsgEX &msg )
{
	if( (msg.opt == MsgEX::msgType::r1 && msg.arg[0] == 34) ||
		msg.opt == MsgEX::msgType::r2j )
	{
		if( cpu.isFree_pc() )
			clearLine();
		cpu.lockPc();
		return 1;
	}
	return 0;
}
void Mips::unlock_pc( const MsgMEM &msg )
{
	if( (msg.opt == MsgMEM::msgType::r1 && msg.arg[0] == 34) ||
		msg.opt == MsgMEM::msgType::r2j )
	{
		cpu.unlockPc();
		if( cpu.isFree_pc() )
		{
			//...
		}
	}
}


void Mips::run( const std::string &File, std::istream *I, std::ostream *O )
{
	mipsDebug::initialize();
	insInput.initialize( File );

	cpu.set_i(I);
	cpu.set_o(O);
	MsgIF mif;
	MsgID mid;
	MsgEX mex;
	MsgMEM mmem;
	MsgWB mwb;
	int steps = 0;
	bool running = 0;
	//bool stepInformation = 1, stepInformation_detail = 1;//, stepOut = 1;
	do{
		using namespace std;
		//int nowPc = cpu.pc();
		steps++;

		if( steps == 23 )
			steps = 23;

		running = 0;
		if( mipsDebug::stepInformation )
		{
			cerr << "\n[ Step: " << steps << " ]" << endl;

		}


		if( memFull && !wbFull )
		{
				mwb = writeBack.run( msgmem );
				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Write Back:\n";
					cerr << mipsDebug::tostr(mwb) << endl;
				if( msgmem.lpc )
					unlock_pc( msgmem );
				msgwb = mwb;
				wbFull = 1;
				memFull = 0;

				if( mipsDebug::lockInformation_detail )
					cerr << mipsDebug::regLocks( &cpu ) << endl;

				running = 1;

		}else{
			if( mipsDebug::stepInformation_detail )
				cerr << "WB stop now.\n";
		}

		if( exFull && !memFull )

		{
				mmem = memAceess.run( msgex );
				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Memory Access:\n";
					cerr << mipsDebug::tostr(mmem) << endl;
				msgmem = mmem;
				memFull = 1;
				exFull = 0;

				running = 1;


		}else{

			if( mipsDebug::stepInformation_detail )
				cerr << "MEM stop now.\n";
		}

		if( idFull && !exFull )
		{
				mex = execute.run( msgid );

				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Execute:\n";
					cerr << mipsDebug::tostr(mex) << endl;

				if( Instruction::Inst::b <= mid.opt && mid.opt <= Instruction::Inst::bltz )
				{
					if(lock_pc( mex ))
						mex.lpc = 1;
				}
				msgex = mex;
				exFull = 1;
				idFull = 0;

				running = 1;


		}else{

			if( mipsDebug::stepInformation_detail )
				cerr << "EX stop now.\n";
		}

		if( ifFull && !idFull )
		{
			if( insDecode.isFree( msgif ) ){
				mid = insDecode.run( msgif );
				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Instruction Decode:\n";
					cerr << mipsDebug::tostr(mid) << endl;
				if( mid.opt == Instruction::Inst::b ||
					( Instruction::Inst::j <= mid.opt && mid.opt <= Instruction::Inst::jalr ) )
				{
					cpu.pc() = mid.arg[0];
				}else if( Instruction::Inst::b <= mid.opt && mid.opt <= Instruction::Inst::bltz )
				{
					//cpu.pc() = mid.arg[0];
				}
				msgid = mid;
				idFull = 1;
				ifFull = 0;

				running = 1;
			}else{

				if( mipsDebug::stepInformation_detail )
					cerr << "ID locked now.\n";
			}

			if( mipsDebug::lockInformation_detail )
				cerr << mipsDebug::regLocks( &cpu ) << endl;

		}else{

			if( mipsDebug::stepInformation_detail )
				cerr << "ID stop now.\n";
		}

		if( mipsDebug::stepInformation )
			cerr << mipsDebug::nowLine( cpu.pc() ) << endl;

		if( cpu.pc() < cpu.pcTop && !ifFull )
		{
			if( insFetch.isFree() ){
				mif = insFetch.run();
				if( mipsDebug::stepInformation_detail )
					//cerr << "Instruction Fetch:\n";
					cerr << mipsDebug::tostr(mif) << endl;
				msgif = mif;
				ifFull = 1;

				running = 1;
			}else{

				if( mipsDebug::stepInformation_detail )
					cerr << "IF locked now.\n";
			}
		}else{			
			if( mipsDebug::stepInformation_detail )
				cerr << "IF stop now.\n";

		}

		if( !running )
			throw 0;
			//break;


		//cerr << "done\n";
		if( wbFull )
		{
			wbFull = 0;
			if(msgwb.opt == MsgWB::msgType::exit || msgwb.opt == MsgWB::msgType::exit0)
				break;
		}
		/*
		if( cpu.pc() >= cpu.pcTop )
			break;*/
	}while(1);
	if( mipsDebug::returnInformation && mipsDebug::debugMode )
	{
		if( mwb.opt == MsgWB::msgType::exit0 )
			std::cerr << "return " << mwb.arg << std::endl;
		else
			std::cerr << "return without argument." << std::endl;
	}

}
