#include "debug.h"

#include "instruction.h"
#include "cpu.h"
#include <sstream>
#include <iostream>



void mipsDebug::initialize()
{
	init_id();
	init_ex();
	init_mem();
	init_wb();
}

std::map<int, std::string>
	mipsDebug::opt_msgid, mipsDebug::opt_msgex,
	mipsDebug::opt_msgmem, mipsDebug::opt_msgwb,
	mipsDebug::lineContent;

std::map<int, int>
	mipsDebug::lineNumber;

bool mipsDebug::debugMode = 0,
	 mipsDebug::stepInformation = 0, mipsDebug::stepInformation_detail = 0,
	 mipsDebug::insInputInformation = 0, mipsDebug::returnInformation = 0,
	 mipsDebug::lockInformation = 0, mipsDebug::lockInformation_detail = 0;

AMutex mipsDebug::lock;

std::string mipsDebug::tostr( const MsgIF &msg )
{
	std::stringstream ss;
	for( int i=0; i<12; ++i )
		ss << int(msg.str[i]) << " ";
	std::string str;
	getline( ss, str );
	return str;
}
std::string mipsDebug::tostr( const MsgID &msg )
{
	std::stringstream ss;
	ss << opt_msgid[msg.opt] << "\t" << msg.narg << "\t";
	for( int i=0; i<5; ++i )
		ss << msg.arg[i] << " ";
	std::string str;
	getline( ss, str );
	return str;
}
std::string mipsDebug::tostr( const MsgEX &msg )
{
	std::stringstream ss;
	ss << opt_msgex[msg.opt] << "\t" ;
	for( int i=0; i<3; ++i )
		ss << msg.arg[i] << " ";
	std::string str;
	getline( ss, str );
	return str;
}
std::string mipsDebug::tostr( const MsgMEM &msg )
{
	std::stringstream ss;
	ss << opt_msgmem[msg.opt] << "\t" ;
	for( int i=0; i<2; ++i )
		ss << msg.arg[i] << " ";
	std::string str;
	getline( ss, str );
	return str;
}
std::string mipsDebug::tostr( const MsgWB &msg )
{
	std::stringstream ss;
	ss << opt_msgwb[msg.opt] << "\t" ;
	ss << msg.arg << " ";
	std::string str;
	getline( ss, str );
	return str;
}

std::string mipsDebug::nowLine( int pc )
{
	std::stringstream ss;
	if( lineNumber.find(pc) == lineNumber.end() )
	{
		ss << "ErrorLine" ;
	}else{
		int id = lineNumber[pc];
		ss << "[" << id << "] ";
		ss << lineContent[ id ] ;
	}
	std::string str;
	getline( ss, str );
	return str;
}

std::string mipsDebug::regLocks( CPU *cpu )
{
	std::string str;
	/*
	for(int ii=0;ii<35;++ii)
	{
		if(cpu->locked[ii])
			str = str + "1";
		else
			str = str + "0";
		if(ii%10==9)
			str = str + "\n";
		else
			str = str + " ";
	}
	*/
	return str;
}

void mipsDebug::init_id()
{
	opt_msgid[Instruction::Inst::add] = "add";
	opt_msgid[Instruction::Inst::addu] = "addu";
	opt_msgid[Instruction::Inst::addiu] = "addiu";
	opt_msgid[Instruction::Inst::sub] = "sub";
	opt_msgid[Instruction::Inst::subu] = "subu";
	opt_msgid[Instruction::Inst::mul] = "mul";
	opt_msgid[Instruction::Inst::mulu] = "mulu";
	opt_msgid[Instruction::Inst::div] = "div";
	opt_msgid[Instruction::Inst::divu] = "divu";
	opt_msgid[Instruction::Inst::xor0] = "xor";
	opt_msgid[Instruction::Inst::xoru] = "xoru";
	opt_msgid[Instruction::Inst::neg] = "neg";
	opt_msgid[Instruction::Inst::negu] = "negu";
	opt_msgid[Instruction::Inst::rem] = "rem";
	opt_msgid[Instruction::Inst::remu] = "remu";
	opt_msgid[Instruction::Inst::li] = "li";
	opt_msgid[Instruction::Inst::seq] = "seq";
	opt_msgid[Instruction::Inst::sge] = "sge";
	opt_msgid[Instruction::Inst::sgt] = "sgt";
	opt_msgid[Instruction::Inst::sle] = "sle";
	opt_msgid[Instruction::Inst::slt] = "slt";
	opt_msgid[Instruction::Inst::sne] = "sne";
	opt_msgid[Instruction::Inst::b] = "b";
	opt_msgid[Instruction::Inst::beq] = "beq";
	opt_msgid[Instruction::Inst::bne] = "bne";
	opt_msgid[Instruction::Inst::bge] = "bge";
	opt_msgid[Instruction::Inst::ble] = "ble";
	opt_msgid[Instruction::Inst::bgt] = "bgt";
	opt_msgid[Instruction::Inst::blt] = "blt";
	opt_msgid[Instruction::Inst::beqz] = "beqz";
	opt_msgid[Instruction::Inst::bnez] = "bnez";
	opt_msgid[Instruction::Inst::blez] = "blez";
	opt_msgid[Instruction::Inst::bgez] = "bgez";
	opt_msgid[Instruction::Inst::bgtz] = "bgtz";
	opt_msgid[Instruction::Inst::bltz] = "bltz";
	opt_msgid[Instruction::Inst::j] = "j";
	opt_msgid[Instruction::Inst::jr] = "jr";
	opt_msgid[Instruction::Inst::jal] = "jal";
	opt_msgid[Instruction::Inst::jalr] = "jalr";
	opt_msgid[Instruction::Inst::la] = "la";
	opt_msgid[Instruction::Inst::lb] = "lb";
	opt_msgid[Instruction::Inst::lh] = "lh";
	opt_msgid[Instruction::Inst::lw] = "lw";
	opt_msgid[Instruction::Inst::sb] = "sb";
	opt_msgid[Instruction::Inst::sh] = "sh";
	opt_msgid[Instruction::Inst::sw] = "sw";
	opt_msgid[Instruction::Inst::move] = "move";
	opt_msgid[Instruction::Inst::mfhi] = "mfhi";
	opt_msgid[Instruction::Inst::mflo] = "mflo";
	opt_msgid[Instruction::Inst::nop] = "nop";
	opt_msgid[Instruction::Inst::syscall] = "syscall";
	opt_msgid[Instruction::Inst::mul2] = "mul2";
	opt_msgid[Instruction::Inst::mulu2] = "mulu2";
	opt_msgid[Instruction::Inst::div2] = "div2";
	opt_msgid[Instruction::Inst::divu2] = "divu2";
}

void mipsDebug::init_ex()
{
	opt_msgex[MsgEX::msgType::non] = "non";
	opt_msgex[MsgEX::msgType::r1] = "r1";
	opt_msgex[MsgEX::msgType::r2lh] = "r2lh";
	opt_msgex[MsgEX::msgType::r2j] = "r2j";
	opt_msgex[MsgEX::msgType::load] = "load";
	opt_msgex[MsgEX::msgType::store] = "store";
	opt_msgex[MsgEX::msgType::oInt] = "oInt";
	opt_msgex[MsgEX::msgType::oStr] = "oStr";
	opt_msgex[MsgEX::msgType::iInt] = "iInt";
	opt_msgex[MsgEX::msgType::iStr] = "iStr";
	opt_msgex[MsgEX::msgType::space] = "space";
	opt_msgex[MsgEX::msgType::exit] = "exit";
	opt_msgex[MsgEX::msgType::exit0] = "exit0";
}

void mipsDebug::init_mem()
{
	opt_msgmem[MsgMEM::msgType::non] = "non";
	opt_msgmem[MsgMEM::msgType::r1] = "r1";
	opt_msgmem[MsgMEM::msgType::r2lh] = "r2lh";
	opt_msgmem[MsgMEM::msgType::r2j] = "r2j";
	opt_msgmem[MsgMEM::msgType::exit] = "exit";
	opt_msgmem[MsgMEM::msgType::exit0] = "exit0";
}

void mipsDebug::init_wb()
{
	opt_msgwb[MsgWB::msgType::non] = "non";
	opt_msgwb[MsgWB::msgType::exit] = "exit";
	opt_msgwb[MsgWB::msgType::exit0] = "exit0";
}
