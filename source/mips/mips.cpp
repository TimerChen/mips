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
	do{
		mif = insFetch.run();
		mid = insDecode.run( mif );
		mex = execute.run( mid );
		mmem = memAceess.run( mex );
		mwb = writeBack.run( mmem );
		if( mwb.opt == MsgWB::msgType::exit || mwb.opt == MsgWB::msgType::exit0 )
			break;
	}while(1);
	if( mwb.opt == MsgWB::msgType::exit0 )
		std::cerr << "return " << mwb.arg << std::endl;
	else
		std::cerr << "return without argument." << std::endl;
}
