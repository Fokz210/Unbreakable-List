#include <fstream>
#include "Processor.h"

int main (int argv, char ** argc)
{
	const char * data = (argv == 1) ? "code.icp" : argc[1];

	Processor proc;

	std::ifstream code (data);
	proc.read (code); 
	code.close ();

	proc.run (std::cout);

	system ("pause");
	return 0;
}
