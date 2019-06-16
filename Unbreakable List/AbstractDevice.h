#pragma once
#include <vector>

class AbstractDevice
{
public:
	AbstractDevice (int portsNum);
	AbstractDevice ();

	virtual void Run () = 0;

	std::vector <float> ports_;
};

