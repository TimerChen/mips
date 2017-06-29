#ifndef DEVICE_H
#define DEVICE_H


class Device
{
public:
	Device();
	lock();
	unlock();
private:
	bool locked;
};

#endif // DEVICE_H
