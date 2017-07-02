#ifndef INSFETCH_H
#define INSFETCH_H

#include "cpu.h"
#include "instruction.h"
#include "msg.h"

#include "stage.h"

class InsFetch : public Stage
{
public:
	InsFetch( CPU *cpuAdress );
	MsgIF run();
private:

};

#endif // INSFETCH_H
