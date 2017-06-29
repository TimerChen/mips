#include "msg.h"

Msg0::Msg0(const char *Str)
{
	str = new char [12];
	for( int i=0; i<12; ++i )
		str[i] = Str[i];
}
Msg0::~Msg0()
{
	delete [] str;
}
