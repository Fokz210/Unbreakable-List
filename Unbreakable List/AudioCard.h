#pragma once
#include "AbstractDevice.h"
class AudioCard :
	public AbstractDevice
{
public:
	AudioCard ();

	virtual void Run () override;
};

