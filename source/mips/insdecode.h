#ifndef INSDECODE_H
#define INSDECODE_H

#include "stage.h"
#include "instruction.h"
#include "msg.h"

class InsDecode : public Stage
{
public:
	InsDecode( CPU *cpuAdress, Forwarder *forwarder );
	bool isFree( const MsgIF &msgIF );
	void work();
	MsgID run(const MsgIF &msg);
private:
};

#endif // INSDECODE_H
