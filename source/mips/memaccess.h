#ifndef MEMACCESS_H
#define MEMACCESS_H

#include "stage.h"
#include "msg.h"

class MemAccess : public Stage
{
public:
	MemAccess( CPU* cpuAdress );
	MsgMEM run( const MsgEX &msgEX );
};

#endif // MEMACCESS_H
