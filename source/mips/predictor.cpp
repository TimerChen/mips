#include "predictor.h"

Predictor::Predictor()
{

}

void Predictor::move( const char &add, const char &next )
{
	char &history = his[add];
	char &m = mode[add][history];
	if( !next && m > 0 )
		m--;
	else if( next && m < 3 )
		m++;
}
char Predictor::hash( const unsigned int &address )
{
	return ( (address/12) & 15 );
}

void Predictor::step( const unsigned int &address, const char &next )
{
	char add = hash(address);
	char &history = his[add];
	move( add, next );
	history = ( ( (history << 1) | next ) & 15 );
}
bool Predictor::predict( const unsigned int &address )
{
	char add = hash( address );
	return mode[add][his[ hash(address) ]] > 1 ? 1 : 0;
}
