#ifndef MIPS_H
#define MIPS_H

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

#include "cpu.h"
#include "instruction.h"

#include "insinput.h"

#include "insfetch.h"
#include "insdecode.h"
#include "execute.h"
#include "memaccess.h"
#include "writeback.h"


class Mips
{
public:
	Mips(unsigned int MEMSIZE = 32*1024*1024);
	~Mips();
	void run( const std::string &File );
private:
	CPU cpu;
	InsInput insInput;
//	InsFetch insFetch;
//	InsDecode insDecode;
//	Execute execute;
//	MemAccess memAceess;
//	WriteBack writeBack;
};


#endif // MIPS_H










