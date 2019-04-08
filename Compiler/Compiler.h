#pragma once
#include "../Unbreakable List/Stack.h"
#include <iostream>
#include <string>

class Compiler
{
public:

	enum comms
	{
		push,
		add, sub, div, mul,
		pop
	};

	Compiler ();
	~Compiler ();

	bool compile (std::istream & file);
	bool write (std::ostream & file);

private:
	icl::vector <int> code_;
};

