#ifndef Stage_H
#define Stage_H

#include "cpu.h"
#include "forwarder.h"

class Stage
{
public:
	Stage( CPU *cpuAdress, Forwarder *forwarder );
	static void WORK( Stage *s );
	virtual void work()=0;
protected:
	CPU *cpu;
	Forwarder *fwd;
};

#endif // Stage_H
