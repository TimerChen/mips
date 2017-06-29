#include "mips.h"

Mips::Mips(unsigned int MEMSIZE)
	:cpu(MEMSIZE),insInput(&cpu)
{

}

Mips::~Mips()
{

}

void Mips::run(const std::string &File)
{
	insInput.initialize( File );

}
