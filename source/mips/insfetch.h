#ifndef INSFETCH_H
#define INSFETCH_H

#include "cpu.h"
#include "instruction.h"
#include "msg.h"

#include "stage.h"

class InsFetch : public Stage
{
public:
	InsFetch( CPU *cpuAdress, Forwarder *forwarder );
	void work();

	bool isFree();
private:
	MsgIF run();
};

#endif // INSFETCH_H
