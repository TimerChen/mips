#include "msg.h"

MsgIF::MsgIF(const char *Str)
{
	for( int i=0; i<12; ++i )
		str[i] = Str[i];
}

MsgID::MsgID()
{
	opt = narg = 0;
	for( int i=0; i<5; ++i )
		arg[i] = 0;
}


MsgEX::MsgEX()
{
	opt = arg[0] = arg[1] = 0;
}

MsgMEM::MsgMEM()
{
	idx = 0;
	arg = 0;
}
