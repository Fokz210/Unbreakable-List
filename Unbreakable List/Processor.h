#pragma once
#include <iostream>
#include <string>
#include "Stack.h"

class Processor
{
public:
	
	enum comms
	{
		push,
		add, sub, div, mul,
		pop
	};

	struct procUnit
	{
		comms command = push;
		int input = 0;
	};

	Processor ();
	~Processor ();

	void run (std::ostream & file);
	void read (std::istream & file);

private:
	icl::stack <int> stack_;
	icl::vector <procUnit> code_;
};

