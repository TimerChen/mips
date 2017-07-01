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
	short stepInformation = 1;//, stepOut = 1;
	do{
		using namespace std;
		int nowPc = cpu.pc();

		steps++;
		mif = insFetch.run();
		mid = insDecode.run( mif );
		mex = execute.run( mid );
		mmem = memAceess.run( mex );
		mwb = writeBack.run( mmem );

		if( stepInformation )
		{
			cerr << "\n[ Step: " << steps << " ]" << endl;
			cerr << mipsDebug::nowLine( nowPc ) << endl;

			//cerr << "Instruction Fetch:\n";

			cerr << mipsDebug::tostr(mif) << endl;

			//cerr << "done\n" << "Instruction Decode:\n";
			cerr << mipsDebug::tostr(mid) << endl;

			//cerr << "done\n" << "Execute:\n";
			cerr << mipsDebug::tostr(mex) << endl;

			//cerr << "done\n" << "Memory Access:\n";
			cerr << mipsDebug::tostr(mmem) << endl;

			//cerr << "done\n" << "Write Back:\n";
			cerr << mipsDebug::tostr(mwb) << endl;
		}
		//cerr << "done\n";
		if( mwb.opt == MsgWB::msgType::exit || mwb.opt == MsgWB::msgType::exit0 )
			break;
		if( cpu.pc() >= cpu.pcTop )
			break;
	}while(1);
	if( mwb.opt == MsgWB::msgType::exit0 )
		std::cerr << "return " << mwb.arg << std::endl;
	else
		std::cerr << "return without argument." << std::endl;
}
