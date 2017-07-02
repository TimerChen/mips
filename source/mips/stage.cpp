#include "stage.h"

Stage::Stage( CPU *cpuAdress )
	:cpu(cpuAdress)
{
	locked = 0;
}
bool Stage::isFree()
	{ return !locked; }
void Stage::lock()
	{ locked = 1; }
void Stage::unlock()
	{ locked = 0; }
