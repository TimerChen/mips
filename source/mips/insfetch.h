#ifndef INSFETCH_H
#define INSFETCH_H

#include "cpu.h"
#include "instruction.h"

#include "device.h"

class InsFetch : public Device
{
public:
	InsFetch( CPU *cpuAdress );
	void getIns();
private:
	short locked;
	CPU *cpu;

};

#endif // INSFETCH_H
