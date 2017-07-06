#ifndef DEBUG_H
#define DEBUG_H

#include "msg.h"

#include "amutex.h"

#include <map>

class CPU;

class mipsDebug
{
public:
	//mipsDebug();

	static void initialize();
	static void init_id();
	static void init_ex();
	static void init_mem();
	static void init_wb();

	static std::map<int, std::string>
		opt_msgid, opt_msgex, opt_msgmem, opt_msgwb,
		lineContent;
	static std::map<int, int>
		lineNumber;

	static AMutex lock;

	static bool debugMode,
				stepInformation, stepInformation_detail,
				insInputInformation, returnInformation,
				lockInformation, lockInformation_detail;

	static std::string tostr( const MsgIF &msg );
	static std::string tostr( const MsgID &msg );
	static std::string tostr( const MsgEX &msg );
	static std::string tostr( const MsgMEM &msg );
	static std::string tostr( const MsgWB &msg );

	static std::string nowLine( int pc );
	static std::string regLocks( CPU *cpu );

};

#endif // DEBUG_H
