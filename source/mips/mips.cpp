#include "mips.h"

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
	insInput.initialize( File );
	cpu.set_i(I);
	cpu.set_o(O);
	MsgIF mif;
	MsgID mid;
	MsgEX mex;
	MsgMEM mmem;
	MsgWB mwb;
	int steps = 0;
	do{
		using namespace std;
		steps++;
		cerr << "\n[ Step: " << steps << " ]" << endl;
		//cerr << "Instruction Fetch...";
		mif = insFetch.run();
		//cerr << "done\n" << "Instruction Decode...";
		mid = insDecode.run( mif );
		//cerr << "done\n" << "Execute...";
		mex = execute.run( mid );
		//cerr << "done\n" << "Memory Access...";
		mmem = memAceess.run( mex );
		//cerr << "done\n" << "Write Back...";
		mwb = writeBack.run( mmem );
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
