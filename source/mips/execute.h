#ifndef EXECUTE_H
#define EXECUTE_H

#include "stage.h"
#include "instruction.h"
#include "msg.h"

class Execute : public Stage
{
public:
	Execute( CPU *cpuAdress, Forwarder *forwarder );

	void work();
private:
	MsgEX run( const MsgID &msgID );
};

#endif // EXECUTE_H
