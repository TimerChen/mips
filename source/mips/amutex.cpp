#include "amutex.h"

#include <thread>
#include <iostream>

#include "debug.h"

AMutex::AMutex()
:af( ATOMIC_FLAG_INIT )
{}

bool AMutex::try_lock()
{
	return af.test_and_set(std::memory_order_acquire);
}

void AMutex::lock()
{

	if( mipsDebug::lockInformation )
		std::cerr << this << " wait for lock." << std::endl;
	//while( af.test_and_set() )
	while( af.test_and_set(std::memory_order_acquire) )
	//while( af.exchange(1) )
		std::this_thread::yield();
	if( mipsDebug::lockInformation )
		std::cerr << this << " locked." << std::endl;
}

void AMutex::unlock()
{
	//af.clear();
	af.clear(std::memory_order_release);
	//af.store( 0 );
	if( mipsDebug::lockInformation )
		std::cerr << this << " unlocked." << std::endl;
}
