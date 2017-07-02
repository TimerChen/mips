#ifndef WRITEBACK_H
#define WRITEBACK_H

#include "msg.h"
#include "stage.h"


class WriteBack : public Stage
{
public:
	WriteBack( CPU *cpuAdress );
	MsgWB run( const MsgMEM &msgMEM );
private:
};

#endif // WRITEBACK_H
