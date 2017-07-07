#include "predictor.h"

#include <iostream>
#include <cstring>
/*
const int
Predictor::BIT = (1 << 5),
Predictor::BACK = (1 << 5);
*/
Predictor::Predictor()
{
	tot = failed = 0;

	memset( his,0,sizeof(his) );
	memset( mode,0,sizeof(mode) );
}

void Predictor::move( const char &add, const char &next )
{
	//char add = hash(address);
	char &history = his[add];
	//std::cerr << (int)add << "|"<< (int)history << std::endl;
	char &m = mode[add][history];
	if( !next && m > 0 )
		m--;
	else if( next && m < 3 )
		m++;
}
char Predictor::hash( const int &address )
{
	return ( (address/12) & (16-1) );
}

void Predictor::step( const int &address, const char &next )
{
	char add = hash(address);
	char &history = his[add];
	move( add, next );
	history = ( ( (history << 1) | next ) & (16-1) );

}
bool Predictor::predict( const int &address )
{
	//return 1;

	tot++;
	//std::cerr << (int)failed << ","<< (int)tot << std::endl;
	char add = hash( address );
	return mode[add][his[ add ]] > 1 ? 1 : 0;
}
void Predictor::fail()
{
	failed++;
}

double Predictor::suc()
{
	return 1-1.*failed/tot;
}
