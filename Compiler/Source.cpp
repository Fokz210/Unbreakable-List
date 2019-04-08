#include "Compiler.h"
#include <fstream>

int main (int argv, char ** argc)
{
	Compiler comp;

	std::ifstream source ("source.ics");
	comp.compile (source);
	source.close ();

	std::ofstream code ("../Unbreakable List/code.icp");
	comp.write (code);
	code.close();

	return 0;
}