#pragma once
#include <iostream>
#include <string>
#include "Stack.h"
#include <vector>
#include <stack>

class Processor
{
public:
	
	enum comms
	{
		push, pop,
		add, sub, div, mul,
		in, out,
		push_reg, pop_reg,
		push_mem, push_mem_reg, push_mem_reg_add
	};

	Processor ();
	~Processor ();

	void run (std::ostream & file);
	bool read (std::istream & file);

private:
	icl::stack <int> stack_;
	std::vector <int> code_;
	std::vector <int> registers_;
	std::vector <int> memory_;
};

