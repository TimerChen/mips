#include "instruction.h"

Instruction::Instruction(
		const unsigned short &OPT, const unsigned short &ARG0,
		const unsigned int &ARG1, const unsigned int &ARG2 )
		:opt(OPT), arg0(ARG0), arg1(ARG1), arg2(ARG2){}
