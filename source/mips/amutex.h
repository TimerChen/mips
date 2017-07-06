#ifndef AMUTEX_H
#define AMUTEX_H

#include <atomic>

//Atomic_Mutex
class AMutex
{
public:

	AMutex();

	bool try_lock();
	void lock();
	void unlock();

private:
	std::atomic_flag af;
};

#endif // AMUTEX_H
