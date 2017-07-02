#ifndef EXECUTE_H
#define EXECUTE_H

#include "stage.h"
#include "instruction.h"
#include "msg.h"

class Execute : public Stage
{
public:
	Execute( CPU *cpuAdress );

	MsgEX run( const MsgID &msgID );
private:

};

#endif // EXECUTE_H
