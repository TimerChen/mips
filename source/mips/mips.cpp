#include "mips.h"

#include "debug.h"

Mips::Mips(unsigned int MEMSIZE)
	:cpu(MEMSIZE),insInput(&cpu),
	  insFetch(&cpu), insDecode(&cpu), execute(&cpu),
	  memAceess(&cpu), writeBack(&cpu)
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
		if( steps == 145 )
			steps = 145;
		if( mipsDebug::stepInformation )
		{
			cerr << "\n[ Step: " << steps << " ]" << endl;
			cerr << mipsDebug::nowLine( nowPc ) << endl;
		}

		mif = insFetch.run();
		if( mipsDebug::stepInformation_detail )
			//cerr << "Instruction Fetch:\n";
			cerr << mipsDebug::tostr(mif) << endl;

		mid = insDecode.run( mif );
		if( mipsDebug::stepInformation_detail )
			//cerr << "done\n" << "Instruction Decode:\n";
			cerr << mipsDebug::tostr(mid) << endl;

		mex = execute.run( mid );
		if( mipsDebug::stepInformation_detail )
			//cerr << "done\n" << "Execute:\n";
			cerr << mipsDebug::tostr(mex) << endl;

		mmem = memAceess.run( mex );
		if( mipsDebug::stepInformation_detail )
			//cerr << "done\n" << "Memory Access:\n";
			cerr << mipsDebug::tostr(mmem) << endl;

		mwb = writeBack.run( mmem );
		if( mipsDebug::stepInformation_detail )
			//cerr << "done\n" << "Write Back:\n";
			cerr << mipsDebug::tostr(mwb) << endl;

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
