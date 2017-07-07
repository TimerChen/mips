#include "insinput.h"
#include "instruction.h"
#include "debug.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>


InsInput::InsInput(CPU *CpuAddress):cpu(CpuAddress)
{ ptr = 0; buffer = ""; initRegs(); initPInst(); initInst(); }
void InsInput::initRegs()
{
	std::string str;
	for(int i = 0; i<32; ++i )
	{
		ss.clear();
		ss << '$' << i;
		ss >> str;
		regs[str] = i;
	}
	int j=0;
	regs["$zero"] = j++;
	regs["$at"] = j++;
	for(int i = 0; i < 2; ++i )
	{
		ss.clear();
		ss << "$v" << i;
		ss >> str;
		regs[str] = j++;
	}
	for(int i = 0; i < 4; ++i )
	{
		ss.clear();
		ss << "$a" << i;
		ss >> str;
		regs[str] = j++;
	}
	for(int i = 0; i < 8; ++i )
	{
		ss.clear();
		ss << "$t" << i;
		ss >> str;
		regs[str] = j++;
	}
	for(int i = 0; i < 8; ++i )
	{
		ss.clear();
		ss << "$s" << i;
		ss >> str;
		regs[str] = j++;
	}
	for(int i = 8; i < 10; ++i )
	{
		ss.clear();
		ss << "$t" << i;
		ss >> str;
		regs[str] = j++;
	}
	j = 28;
	regs["$gp"] = j++;
	regs["$sp"] = j++;
	regs["$fp"] = j++;
	regs["$ra"] = j++;
	ss.str("");
}
void InsInput::initPInst()
{
	pinsts[".align"]		= 0;
	pinsts[".ascii"]		= 1;
	pinsts[".asciiz"]		= 2;
	pinsts[".byte"]			= 3;
	pinsts[".half"]			= 4;
	pinsts[".word"]			= 5;
	pinsts[".space"]		= 6;
	pinsts[".data"]			= 7;
	pinsts[".text"]			= 8;
}
void InsInput::initInst()
{
	insts["add"]             = 0;
	insts["addu"]            = 1;
	insts["addiu"]           = 2;
	insts["sub"]             = 3;
	insts["subu"]            = 4;
	insts["mul"]             = 5;
	insts["mulu"]            = 6;
	insts["div"]             = 7;
	insts["divu"]            = 8;
	insts["xor"]             = 9;
	insts["xoru"]            = 10;
	insts["neg"]             = 11;
	insts["negu"]            = 12;
	insts["rem"]             = 13;
	insts["remu"]            = 14;
	insts["li"]              = 15;
	insts["seq"]             = 16;
	insts["sge"]             = 17;
	insts["sgt"]             = 18;
	insts["sle"]             = 19;
	insts["slt"]             = 20;
	insts["sne"]             = 21;
	insts["b"]               = 22;
	insts["beq"]             = 23;
	insts["bne"]             = 24;
	insts["bge"]             = 25;
	insts["ble"]             = 26;
	insts["bgt"]             = 27;
	insts["blt"]             = 28;
	insts["beqz"]            = 29;
	insts["bnez"]            = 30;
	insts["blez"]            = 31;
	insts["bgez"]            = 32;
	insts["bgtz"]            = 33;
	insts["bltz"]            = 34;
	insts["j"]               = 35;
	insts["jr"]              = 36;
	insts["jal"]             = 37;
	insts["jalr"]            = 38;
	insts["la"]              = 39;
	insts["lb"]              = 40;
	insts["lh"]              = 41;
	insts["lw"]              = 42;
	insts["sb"]              = 43;
	insts["sh"]              = 44;
	insts["sw"]              = 45;
	insts["move"]            = 46;
	insts["mfhi"]            = 47;
	insts["mflo"]            = 48;
	insts["nop"]             = 49;
	insts["syscall"]         = 50;
}

void InsInput::initialize( const std::string &File )
{
	clear();
	readFile( File );
	makeIns();
}

void InsInput::clear()
{
	labels.clear();
	clearBuffer();
	ptr = 0;
	ss.str("");
	ss.clear();
}

void InsInput::clearBuffer()
	{ buffer = ""; ptr = 0; }

void InsInput::readFile( const std::string &File )
{
	char charBuffer[1024];
	std::string str;
	std::ifstream fin(File);
	if(fin)
	{
		while(!fin.eof())
		{
			fin.get(charBuffer,1000,'\0');
			buffer = buffer + charBuffer;
		}
		fin.close();
		return;
	}
	std::cerr << "File Not Finded." << std::endl;
}
std::string InsInput::getLine()
{
	char cstr[1024];
	int cptr = 0;
	std::string str;
	for(; ptr < buffer.size(); ++ptr )
	if(	   buffer[ptr] == '\n'
		|| buffer[ptr] == '\r'
		|| buffer[ptr] == '\0' )
		{ ptr++; break; }
	else
		cstr[cptr++] = buffer[ptr];
	cstr[cptr] = 0;
	return std::string(cstr);
}
int InsInput::translate( const std::string &a, const short &type )
{
	int re = 0;
	switch (type) {
		case tokenType::label:
		case tokenType::pinst:
		case tokenType::str:
			//ignore
			break;
		case tokenType::inst:
			re = insts[ a ];
			break;
		case tokenType::alabel:
			if( labels.find(a) == labels.end() )
				throw(0);
			re = labels[ a ];
			break;
		case tokenType::num:
			ss.clear();
			ss << a; ss >> re;
			break;
		case tokenType::reg:
			re = regs[ a ];
			break;
		default:
			break;
	}
	return re;
}

std::string InsInput::getWord
	(const std::string &line, unsigned int &i,
	 short &type, const bool &isArg )
{
	while(i < line.size() &&
		  (line[i] == ' ' || line[i] == '\t' || line[i] == '\0' ||
		   line[i] == '(' || line[i] == ',') ) ++i;
	char str[1024];
	int j = 0;
	bool isSp=0,isStr=0;
	type = -1;
	while( i < line.size() &&
		 ( isStr ||
		   ( line[i] != '(' && line[i] != ')' &&
			 line[i] != ' ' && line[i] != ':' &&
			 line[i] != ',' && line[i] != '\t' &&
			 line[i] != '\0' && line[i] != '#' )
		 ) )
	{
		str[j++] = line[i];
		if( !isStr )
		{
			if( line[i] == '\"' )
				isStr = 1;
		}else{
			if( !isSp )
			{
				if( line[i] == '\\' )
					isSp = 1;
				else if( line[i] == '\"' )
					isStr = 0;
			}else{
				j--;
				switch ( line[i] ) {
					case 'a': str[j-1] = '\a'; break;
					case 'b': str[j-1] = '\b'; break;
					case 'f': str[j-1] = '\f'; break;
					case 'n': str[j-1] = '\n'; break;
					case 'r': str[j-1] = '\r'; break;
					case 't': str[j-1] = '\t'; break;
					case 'v': str[j-1] = '\v'; break;
					case '?': str[j-1] = '\?'; break;
					case '0': str[j-1] = '\0'; break;
					default:  str[j-1] = line[i]; break; // " and '
				}
				isSp = 0;
			}
		}
		i++;
	}
	str[j] = 0;
	if( i < line.size() && line[i] == '#' )
		i = line.size();
	if( !j ) return "";

	if( i < line.size() && line[i] == ':' )
		{ i++; type = 0; return std::string(str); }
	else if( str[0] == '.' )
		{ type = 1; return std::string(str+1); }
	else if( ('a' <= str[0] && str[0] <= 'z') || str[0] == '_' )
		{ type = ( isArg?3:2 ); return std::string(str); }
	else if( ('0' <= str[0] && str[0] <= '9') || str[0] == '-' || str[0] == '+' )
		{ type = 4; return std::string(str); }
	else if( str[0] == '\"' )
		{ type = 5; return std::string(str); }
	else if( str[0] == '$' )
		{ type = 6; return std::string(str); }

	//error
	return "";
}
void InsInput::setTop()
{
	std::string line, word;
	short type;
	bool isData = 0;
	int insNum = 0;
	ptr = 0;
	while( ptr < buffer.size() )
	{
		line = getLine();
		unsigned int i = 0;
		if( i < line.size() )
		{
			word = getWord(line, i, type);
			if(type == tokenType::inst)
				insNum++;
			else if( type == tokenType::pinst )
			{
				if( word == "data" )
					isData = 1;
				else if( word == "text" )
					isData = 0;
			}
			else if( type == tokenType::label && !isData )
			{
				labels[word] = insNum * CPU::InsStep;
			}
		}
	}
	cpu->pcTop = cpu->top = insNum * CPU::InsStep;
}
void InsInput::putData()
{

	std::string line,word;
	short type;
	bool isData = 0;
	ptr = 0;

	while( ptr < buffer.size() )
	{
		line = getLine();

		unsigned int i = 0;
		if( i < line.size() )
		{
			word = getWord(line, i, type);
			if(type == -1) continue;
			if( type == tokenType::pinst )
			{
				if( word == "data" )
					isData = 1;
				else if( word == "text" )
					isData = 0;
				else if( isData ){
					if( word == "align" )
					{
						int tmp;
						word = getWord(line, i, type, 1);
						ss.clear();
						ss << word;ss >> tmp;
						tmp = (1<<tmp);
						while( cpu->top % tmp )
							cpu->Memory[cpu->top++] = 0;
					}else if( word == "ascii" ){
						word = getWord(line, i, type, 1);
						word = word.substr( 1, word.size()-2 );
						cpu->top = cpu->write_memStr( cpu->top, word, 0 );
					}else if( word == "asciiz" ){
						word = getWord(line, i, type, 1);
						word = word.substr( 1, word.size()-2 );
						cpu->top = cpu->write_memStr( cpu->top, word, 1 );
					}else if( word == "byte" ){
						while( i < line.size() )
						{
							word = getWord(line, i, type, 1);
							if(type == -1) break;
							char tmp;
							ss.clear();
							ss << word; ss >> tmp;
							*((char*)(cpu->Memory + cpu->top)) = tmp;
							cpu->top += sizeof(tmp);
						}
					}else if( word == "half" ){
						while( i < line.size() )
						{
							word = getWord(line, i, type, 1);
							if(type == -1) break;
							short tmp;
							ss.clear();
							ss << word; ss >> tmp;
							*((short*)(cpu->Memory + cpu->top)) = tmp;
							cpu->top += sizeof(tmp);
						}
					}else if( word == "word" ){
						while( i < line.size() )
						{
							word = getWord(line, i, type, 1);
							if(type == -1) break;
							int tmp;
							ss.clear();
							ss << word; ss >> tmp;
							*((int*)(cpu->Memory + cpu->top)) = tmp;
							cpu->top += sizeof(tmp);
						}
					}else if( word == "space" ){
						word = getWord(line, i, type, 1);
						int tmp;
						ss.clear();
						ss << word; ss >> tmp;
						while(tmp--)
							cpu->Memory[cpu->top++] = 0;
					}else{
						//error
					}
				}
			}else if( type == tokenType::label && isData ){
				labels[word] = cpu->top;
			}
		}
	}

	ss.str("");
}
void InsInput::putInst()
{
	std::string line,word;
	short type;
	bool isData = 0;
	int pcTop = 0;
	Instruction ins;
	ptr = 0;

	int lineNumber = 0;



	while( ptr < buffer.size() )
	{
		lineNumber++;
		ins = Instruction();
		line = getLine();

		mipsDebug::lineContent[ lineNumber ] = line;
		unsigned int i = 0;
		if( i < line.size() )
		{
			word = getWord(line, i, type);
			if( type == tokenType::pinst )
			{
				if( word == "data" )
					isData = 1;
				else if( word == "text" )
					isData = 0;
			}
			else if( type == tokenType::inst )
			{
				mipsDebug::lineNumber[ pcTop ] = lineNumber;
				if( insts.find(word) == insts.end() )
					throw(0);
				ins.opt = insts[ word ];
				std::string args[3];
				int argsi[3];
				short aType[3];
				for(int ii=0;ii<3;++ii)
					args[ii] = getWord(line, i, aType[ii], 1);

				/*
				 *	reg reg reg/num
				 *  reg reg reg/num / reg reg/num
				 *	reg label / reg (num) reg
				 */
				if( aType[1] == -1 && aType[2] == -1 ) // 1
				{
					argsi[0] = translate( args[0], aType[0] );
					if( aType[0] == tokenType::alabel )
						ins.arg3 = argsi[0];
					else	//tokenType::reg
						ins.arg0 = argsi[0];
				}
				else if( aType[2] == -1 ) // 2
				{
					argsi[0] = translate( args[0], aType[0] );
					argsi[1] = translate( args[1], aType[1] );
					ins.arg0 = argsi[0];
					if( aType[1] == tokenType::num || aType[1] == tokenType::alabel )
						ins.arg3 = argsi[1];
					else if( aType[1] == tokenType::reg ) //tokenType::
						ins.arg1 = argsi[1];
					else
						std::cerr << "Error" << std::endl;

					if( Instruction::Inst::mul <= ins.opt  &&
						ins.opt <= Instruction::Inst::divu )
						ins.opt += Instruction::Inst::mul2 - Instruction::Inst::mul;
				}
				else if( aType[0] != -1 ) // 3
				{
					//reg reg reg
					//reg reg number
					//reg reg label
					//reg number label
					//reg number reg
					argsi[0] = translate( args[0], aType[0] );
					argsi[1] = translate( args[1], aType[1] );
					argsi[2] = translate( args[2], aType[2] );
					ins.arg0 = argsi[0];
					if( aType[1] == tokenType::reg )
					{
						ins.arg1 = argsi[1];
						if( aType[2] == tokenType::reg )
							ins.arg2 = argsi[2];
						//aType[2] == tokenType::alabel
						//aType[2] == tokenType::num
						else
							ins.arg3 = argsi[2];
					}else{
						ins.arg3 = argsi[1];
						if( aType[2] == tokenType::reg )
							ins.arg1 = argsi[2];
						else
							ins.arg4 = argsi[2];
					}
				}
				*((Instruction*)(cpu->Memory + pcTop)) = ins;
				if( mipsDebug::insInputInformation )
				{
					std::cerr << mipsDebug::nowLine( pcTop ) << std::endl;
					std::cerr << mipsDebug::opt_msgid[ins.opt] << "\t" << (int)ins.arg0 << " "
							  << (int)ins.arg1 << " " << (int)ins.arg2 << " "
							  << (int)ins.arg3 << " " << (int)ins.arg4 << " "
							  << std::endl;
					for(int ii=0;ii<12;++ii)
						std::cerr << (int)cpu->Memory[pcTop+ii] << " ";
					std::cerr << std::endl;
				}
				pcTop += CPU::InsStep;
			}

		}
	}
}

void InsInput::makeIns()
{
	setTop();
	putData();
	putInst();
	cpu->pc() = labels["main"];
	clear();
}
