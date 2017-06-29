#ifndef DEVICE_H
#define DEVICE_H

#include "cpu.h"

class Device
{
public:
	Device( CPU *cpuAdress );
	bool isFree();
	void lock();
	void unlock();
protected:
	CPU *cpu;
private:

	bool locked;
};

#endif // DEVICE_H
