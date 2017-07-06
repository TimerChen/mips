#include "cpu.h"

#include "error.h"
#include "forwarder.h"
#include <thread>
#include <cstring>

const unsigned CPU::InsStep = 12;

CPU::CPU( Forwarder* forwarder, unsigned int MEMSIZE,
		 std::istream *In, std::ostream *Out)
	:MemSize(MEMSIZE), in(In), out(Out)
{
	fwd = forwarder;
	Memory = new char[MemSize];
	top=0;
	for(int i=0;i<35;++i) reg[i] = 0;
	reg[29] = MemSize-1;
}

CPU::~CPU()
{
	delete [] Memory;
}

unsigned int &CPU::lo()
{ return reg[32]; }

unsigned int &CPU::hi()
{ return reg[33]; }

unsigned int &CPU::pc()
{ return reg[34]; }

unsigned int &CPU::ptop()
{ return top; }

void CPU::write_reg( int idx, int val )
{
	//no lock


	if( idx!=34 )
	{
		while( 1 )
		{
			if( lock[idx].try_lock() )
			{
				std::this_thread::yield();
			}else{
				if( modify_num[idx] )
					modify_num[idx]--;
				reg[idx] = val;
				lock[idx].unlock();
				break;
			}
		}
	}
	else
	{
		reg[idx] = val;
	}
}
void CPU::write_reg_ready( int idx )
{
	if( idx!=34 )
	{
		lock[idx].lock();
		modify_num[idx]++;
		lock[idx].unlock();
	}else{

	}
}

unsigned int CPU::read_reg( int idx )
{
//	if( locked[idx] )
//		throw( RegLocked() );
	unsigned int val;
	while(1)
	{
		if( fwd->clear_idline || fwd->exit )
			break;
		if( lock[idx].try_lock() )
		{
			std::this_thread::yield();
		}else{
			if( modify_num[idx]==0 )
			{
				val = reg[idx];
				lock[idx].unlock();
				break;
			}else
				lock[idx].unlock();
		}
	}
	return val;
}


void CPU::write_mem(int idx, int val, short len)
{
	char tmp[4];
	*((int*)(tmp)) = val;
	for( int i=0; i<len; ++i )
		Memory[idx+i] = tmp[i];
}
unsigned int CPU::read_mem(int idx, short len)
{
	char tmp[4]={};
	int val = 0;
	for( int i=0; i<len; ++i )
		tmp[i] = Memory[idx+i];
	val = *((int*)(tmp));
	return val;
}


unsigned int CPU::write_memStr( int idx, const std::string &str, bool zero )
{

	memcpy( Memory+idx, str.c_str(), (zero + str.size()) );
	return idx + (str.size() + zero);
}
std::string CPU::read_memStr(int idx)
{
	return std::string( Memory + idx );
}

int CPU::read_ioInt()
{
	int val;
	(*in) >> val;
	return val;
}

void CPU::write_ioInt( int val )
{
	(*out) << val;
}

int CPU::read_ioStr( int pos, unsigned int maxLen )
{
	std::string str;
	(*in) >> str;
	maxLen--;
	for( unsigned int i=0; i<maxLen && i<str.size(); ++i )
		Memory[pos++] = str[i];
	Memory[pos++] = 0;
	return pos;
}
void CPU::set_i(std::istream *i)
{
	in = i;
}

void CPU::set_o(std::ostream *o)
{
	out = o;
}

void CPU::write_ioStr( const std::string &str )
{
	(*out) << str;
}

int CPU::newSpace( int len )
{
	while( top % 4 )top++;
	while( len-- )
		Memory[top++] = 0;
	return top;
}
void CPU::clearLockReg()
{
	for( int i=0; i<34; ++i )
	{
		lock[i].lock();
		modify_num[i] = 0;
		lock[i].unlock();
	}
}
