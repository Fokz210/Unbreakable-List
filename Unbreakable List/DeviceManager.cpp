#include "DeviceManager.h"

DeviceManager::DeviceManager () :
	devices_ ()
{
}

void DeviceManager::AddDevice (AbstractDevice* device)
{
	devices_.push_back (device);
}

void DeviceManager::Run ()
{
	for (AbstractDevice* device : devices_)
		device->Run ();
}

void DeviceManager::In (int port, float data)
{
	int i = 0;
	for (AbstractDevice* device : devices_)
	{
		for (float& port_ : device->ports_)
		{
			if (i == port)
				port_ = data;
			i++;
		}
	}
}

float DeviceManager::Out (int port)
{
	int i = 0;
	for (AbstractDevice* device : devices_)
	{
		for (float& port_ : device->ports_)
		{
			if (i == port)
				return port_;
			i++;
		}
	}
}