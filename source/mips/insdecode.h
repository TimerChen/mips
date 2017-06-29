#ifndef INSDECODE_H
#define INSDECODE_H

#include "instruction.h"

class InsDecode
{
public:
	InsDecode();
	Instruction decode(char *ins);

};

#endif // INSDECODE_H
