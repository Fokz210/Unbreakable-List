#include "AbstractDevice.h"

AbstractDevice::AbstractDevice (int portsNum) :
	ports_ (portsNum)
{

}

AbstractDevice::AbstractDevice () :
	ports_ ()
{

}