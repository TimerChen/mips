#include "device.h"

Device::Device()
{
	locked = 0;
}
bool Device::isFree()
	{ return !locked; }
void Device::lock()
	{ locked = 1; }
Device::unlock()
	{ locked = 0; }
