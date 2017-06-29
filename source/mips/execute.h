#ifndef EXECUTE_H
#define EXECUTE_H

#include "device.h"
#include "instruction.h"
#include "msg.h"

class Execute : public Device
{
public:
	Execute( CPU *cpuAdress );

	MsgEX run( const MsgID &msgID );
private:

};

#endif // EXECUTE_H
