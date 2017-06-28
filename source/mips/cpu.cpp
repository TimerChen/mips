#include "cpu.h"

#include <cstring>

const unsigned CPU::InsStep = 12;

CPU::CPU(unsigned int MEMSIZE)
	:MemSize(MEMSIZE)
{
	Memory = new char[MemSize];
	lo=hi=top=pc=0;
	for(int i=0;i<32;++i)reg[i] = 0;
	reg[29] = MemSize-1;
}

CPU::~CPU()
{
	delete [] Memory;
}

unsigned int CPU::write_memStr( int idx, const std::string &str, bool zero )
{

	memcpy( Memory+idx, str.c_str(), (zero + str.size()) );
	return idx + (str.size() + zero);
}
