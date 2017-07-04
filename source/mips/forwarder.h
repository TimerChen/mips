#ifndef FORWARDER_H
#define FORWARDER_H

#include "msg.h"
#include "amutex.h"
#include <atomic>

class Forwarder
{
public:
	Forwarder();
	MsgIF mif;
	MsgID mid;
	MsgEX mex;
	MsgMEM mmem;
	MsgWB mwb;

	bool ok_if, ok_id, ok_ex, ok_mem, ok_wb,
		 clear_if, clear_id;

	//std::atomic_bool exit;
	bool exit;

	AMutex lock_if, lock_id;

//	Forwarder (const Forwarder &) = delete;
//	Forwarder & operator=(const Forwarder &) = delete;
//	Forwarder & operator=(const Forwarder &) volatile = delete;

};

#endif // FORWARDER_H
