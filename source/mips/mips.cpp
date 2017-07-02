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
	//...
}

void Mips::lock_pc( const MsgEX &msg )
{
	if( (msg.opt == MsgMEM::msgType::r1 && msg.arg[0] == 34) ||
		msg.opt == MsgMEM::msgType::r2j )
	{
		if( cpu.isFree_pc() )
			clearLine();
		cpu.lockPc();
	}
}
void Mips::unlock_pc( const MsgMEM &msg )
{
	if( msg.opt != MsgMEM::msgType::non )
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
	//bool stepInformation = 1, stepInformation_detail = 1;//, stepOut = 1;
	do{
		using namespace std;
		int nowPc = cpu.pc();
		steps++;
/*

		mif = insFetch.run();
		mid = insDecode.run( mif );
		mex = execute.run( mid );
		mmem = memAceess.run( mex );
		mwb = writeBack.run( mmem );

		if( mipsDebug::stepInformation )
		{
			cerr << "\n[ Step: " << steps << " ]" << endl;
			cerr << mipsDebug::nowLine( nowPc ) << endl;
		}

			if( mipsDebug::stepInformation_detail )
				//cerr << "Instruction Fetch:\n";
				cerr << mipsDebug::tostr(mif) << endl;

			if( mipsDebug::stepInformation_detail )
				//cerr << "done\n" << "Instruction Decode:\n";
				cerr << mipsDebug::tostr(mid) << endl;

			if( mipsDebug::stepInformation_detail )
				//cerr << "done\n" << "Execute:\n";
				cerr << mipsDebug::tostr(mex) << endl;

			if( mipsDebug::stepInformation_detail )
				//cerr << "done\n" << "Memory Access:\n";
				cerr << mipsDebug::tostr(mmem) << endl;

			if( mipsDebug::stepInformation_detail )
				//cerr << "done\n" << "Write Back:\n";
				cerr << mipsDebug::tostr(mwb) << endl;
*/
		if( mipsDebug::stepInformation )
		{
			cerr << "\n[ Step: " << steps << " ]" << endl;
			cerr << mipsDebug::nowLine( nowPc ) << endl;
		}



		if( memFull )
		{
			try{
				mwb = writeBack.run( msgmem );
				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Write Back:\n";
					cerr << mipsDebug::tostr(mwb) << endl;
				unlock_pc( msgmem );

			}catch(...){

			}
		}else{
			if( mipsDebug::stepInformation_detail )
				cerr << "WB full now.\n";
		}

		if( exFull )

		{
			try{
				mmem = memAceess.run( msgex );
				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Memory Access:\n";
					cerr << mipsDebug::tostr(mmem) << endl;
			}catch(...){

			}

		}else{

			if( mipsDebug::stepInformation_detail )
				cerr << "MEM full now.\n";
		}

		if( idFull )
		{
			try{
				mex = execute.run( msgid );

				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Execute:\n";
					cerr << mipsDebug::tostr(mex) << endl;

				lock_pc( mex );
			}catch(...){

			}

		}else{

			if( mipsDebug::stepInformation_detail )
				cerr << "EX full now.\n";
		}

		if( ifFull )
		{
			try{
				mid = insDecode.run( msgif );
				if( mipsDebug::stepInformation_detail )
					//cerr << "done\n" << "Instruction Decode:\n";
					cerr << mipsDebug::tostr(mid) << endl;
			}catch(...){

			}
		}else{

			if( mipsDebug::stepInformation_detail )
				cerr << "ID full now.\n";
		}

		if( cpu.pc() < cpu.pcTop )
		{
			try{
				mif = insFetch.run();
				ifFull = 1;
				if( mipsDebug::stepInformation_detail )
					//cerr << "Instruction Fetch:\n";
					cerr << mipsDebug::tostr(mif) << endl;
			}catch(...){

			}
		}else{
			if( mipsDebug::stepInformation_detail )
				cerr << "IF full now.\n";
		}




		//cerr << "done\n";
		if( mwb.opt == MsgWB::msgType::exit || mwb.opt == MsgWB::msgType::exit0 )
			break;
		if( cpu.pc() >= cpu.pcTop )
			break;
	}while(1);
	if( mipsDebug::returnInformation && mipsDebug::debugMode )
	{
		if( mwb.opt == MsgWB::msgType::exit0 )
			std::cerr << "return " << mwb.arg << std::endl;
		else
			std::cerr << "return without argument." << std::endl;
	}

}
