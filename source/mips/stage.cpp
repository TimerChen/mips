#include "stage.h"

Stage::Stage( CPU *cpuAdress, Forwarder *forwarder )
	:cpu(cpuAdress), fwd(forwarder)
{}

void Stage::WORK(Stage *s)
{
	s->work();
}
