#include "amutex.h"

#include <thread>

AMutex::AMutex()
:af( ATOMIC_FLAG_INIT )
{}

void AMutex::lock()
{
	//while( af.test_and_set() )
	while( af.test_and_set(std::memory_order_acquire) )
		std::this_thread::yield();
}

void AMutex::unlock()
{
	//af.clear();
	af.clear(std::memory_order_release);
}
