#include "AbstractDevice.h"

#pragma once
class DeviceManager
{
public:
	DeviceManager ();

	void  AddDevice (AbstractDevice* device);
	void  Run ();
	void  In (int port, float data);
	float Out (int port);

protected:
	std::vector <AbstractDevice*> devices_;
};

