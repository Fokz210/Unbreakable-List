#include "Processor.h"
#include <fstream>

int main (int argv, char ** argc)
{
	const char * data = "";

	if (argv == 1)
		data = "code.icp";
	else
		data = argc[1];

	std::ifstream code (data);
	Processor proc;

	proc.read (code);
	proc.run (std::cout);

	code.close ();

	system ("pause");
	return 0;
}