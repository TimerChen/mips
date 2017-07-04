#ifndef WRITEBACK_H
#define WRITEBACK_H

#include "msg.h"
#include "stage.h"


class WriteBack : public Stage
{
public:
	WriteBack( CPU *cpuAdress, Forwarder *forwarder );
	void work();
private:
	MsgWB run( const MsgMEM &msgMEM );
};

#endif // WRITEBACK_H
