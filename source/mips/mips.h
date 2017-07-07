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
#include "msg.h"
#include "predictor.h"


class Mips
{
public:
	Mips(unsigned int MEMSIZE = 128*1024*1024);
	~Mips();
	void run( const std::string &File, std::istream *I = &std::cin, std::ostream *O = &std::cout );
private:
	CPU cpu;
	InsInput insInput;
	InsFetch insFetch;
	InsDecode insDecode;
	Execute execute;
	MemAccess memAceess;
	WriteBack writeBack;

	MsgIF msgif;
	MsgID msgid;
	MsgEX msgex;
	MsgMEM msgmem;
	MsgWB msgwb;

	bool ifFull, idFull, exFull, memFull, wbFull;

	void store( const MsgIF &msg );
	void store( const MsgID &msg );
	void store( const MsgEX &msg );
	void store( const MsgMEM &msg );
	void store( const MsgWB &msg );

	void clearLine();
	bool lock_pc( const MsgEX &msg );
	void unlock_pc( const MsgMEM &msg );

};


#endif // MIPS_H










