#ifndef Stage_H
#define Stage_H

#include "cpu.h"

class Stage
{
public:
	Stage( CPU *cpuAdress );
	bool isFree();
	void lock();
	void unlock();
protected:
	CPU *cpu;
private:

	bool locked;
};

#endif // Stage_H
