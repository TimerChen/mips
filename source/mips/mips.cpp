#include "mips.h"

#include "debug.h"

#include <thread>

Mips::Mips(unsigned int MEMSIZE)
	:cpu( &fwd, MEMSIZE),insInput(&cpu),
	  insFetch(&cpu, &fwd), insDecode(&cpu, &fwd), execute(&cpu, &fwd),
	  memAceess(&cpu, &fwd), writeBack(&cpu, &fwd)
{

}

Mips::~Mips()
{

}



void Mips::run( const std::string &File, std::istream *I, std::ostream *O )
{
	mipsDebug::initialize();
	insInput.initialize( File );

	cpu.set_i(I);
	cpu.set_o(O);
	//bool stepInformation = 1, stepInformation_detail = 1;//, stepOut = 1;
	/*
	do{
		using namespace std;
		//int nowPc = cpu.pc();
		steps++;
		running = 0;


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
		/*
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

				lock_pc( mex );
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
	}while(1);*/

	std::thread th[5]={
	std::thread( Stage::WORK, &insFetch ),
	std::thread( Stage::WORK, &insDecode ),
	std::thread( Stage::WORK, &execute ),
	std::thread( Stage::WORK, &memAceess ),
	std::thread( Stage::WORK, &writeBack ) };

	for( int i=0; i<5; ++i )
	if( th[i].joinable() )
		th[i].join();
	if( mipsDebug::returnInformation && mipsDebug::debugMode )
	{
		if( fwd.mwb.opt == MsgWB::msgType::exit0 )
			std::cerr << "return " << fwd.mwb.arg << std::endl;
		else
			std::cerr << "return without argument." << std::endl;
	}

}
