#include "instruction.h"

Instruction::Instruction()
{
	opt=0;
	arg0=arg1=arg2=63;
	arg3=arg4=0;
}
unsigned int Instruction::to_int0()
{
	int re,*p = &re;
	*((char*)(p++)) = opt;
	*((char*)(p++)) = arg0;
	*((char*)(p++)) = arg1;
	*((char*)(p++)) = arg2;
	return re;
}
void Instruction::set_int0( int val )
{
	int *p = &val;
	opt = *((char*)(p++));
	arg0 = *((char*)(p++));
	arg1 = *((char*)(p++));
	arg2 = *((char*)(p++));
}
		/*const unsigned short &OPT, const unsigned short &ARG0,
		const unsigned int &ARG1, const unsigned int &ARG2 )
		:opt(OPT), arg0(ARG0), arg1(ARG1), arg2(ARG2){}*/
