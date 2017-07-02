#include "device.h"

Device::Device( CPU *cpuAdress )
	:cpu(cpuAdress)
{
	locked = 0;
}
bool Device::isFree()
	{ return !locked; }
void Device::lock()
	{ locked = 1; }
void Device::unlock()
	{ locked = 0; }
