#include "AudioCard.h"
#include "D:/TX/TX/TXLib.h"

AudioCard::AudioCard () :
	AbstractDevice (3)
{
}

void AudioCard::Run ()
{
	if (ports_[0] == 1)
	{
		txPlaySound (std::string (std::to_string ((int)ports_[1]) + std::string (".wav")).c_str (), SND_ASYNC);
		ports_[2] == 1;
	}
	else
	{
		txPlaySound (NULL);
		ports_[2] == 0;
	}

}
