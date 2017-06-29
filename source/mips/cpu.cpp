#include "cpu.h"

#include <cstring>

const unsigned CPU::InsStep = 12;

CPU::CPU(unsigned int MEMSIZE)
	:MemSize(MEMSIZE)
{
	Memory = new char[MemSize];
	top=0;
	for(int i=0;i<35;++i) locked[i] = 0, reg[i] = 0;
	reg[29] = MemSize-1;
}

CPU::~CPU()
{
	delete [] Memory;
}

unsigned int &CPU::lo()
{ return reg[32]; }

unsigned int &CPU::hi()
{ return reg[33]; }

unsigned int &CPU::pc()
{ return reg[34]; }


void CPU::write_reg( int idx, int val )
{ reg[idx] = val; }
unsigned int  CPU::read_reg( int idx )
{ return reg[idx]; }


void CPU::write_mem(int idx, int val, short len)
{
	char tmp[4];
	*((int*)(tmp)) = val;
	for( int i=0; i<len; ++i )
		Memory[idx+i] = tmp[4-len+i];
}
unsigned int CPU::read_mem(int idx, short len)
{
	char tmp[4]={};
	int val = 0;
	for( int i=0; i<len; ++i )
		tmp[4-len+i] = Memory[idx+i];
	val = *((int*)(tmp));
	return val;
}

unsigned int CPU::write_memStr( int idx, const std::string &str, bool zero )
{

	memcpy( Memory+idx, str.c_str(), (zero + str.size()) );
	return idx + (str.size() + zero);
}
