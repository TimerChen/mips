#ifndef MEMACCESS_H
#define MEMACCESS_H

#include "device.h"
#include "msg.h"

class MemAccess : public Device
{
public:
	MemAccess( CPU* cpuAdress );
	MsgMEM run( const MsgEX &msgEX );
};

#endif // MEMACCESS_H
