#ifndef WRITEBACK_H
#define WRITEBACK_H

#include "msg.h"
#include "device.h"


class WriteBack : public Device
{
public:
	WriteBack( CPU *cpuAdress );
	MsgWB run( const MsgMEM &msgMEM );
private:
};

#endif // WRITEBACK_H
