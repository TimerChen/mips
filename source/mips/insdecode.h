#ifndef INSDECODE_H
#define INSDECODE_H

#include "device.h"
#include "instruction.h"
#include "msg.h"

class InsDecode : public Device
{
public:
	InsDecode( CPU *cpuAdress );
	MsgID run(const MsgIF &msg);
private:
};

#endif // INSDECODE_H
