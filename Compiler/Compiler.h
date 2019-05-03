#pragma once
#include "../Unbreakable List/Stack.h"
#include <iostream>
#include <string>

class Compiler
{
public:

	enum regs
	{
		undef,
		ax, bx, cx, dx
	};

	enum comms
	{
		push, pop,
		add, sub, div, mul,
		in, out,
		push_reg, pop_reg,
		push_mem, push_mem_reg, push_mem_reg_add,
		pop_mem, pop_mem_reg, pop_mem_reg_add
	};


	Compiler ();
	~Compiler ();

	bool compile (std::istream & file);
	bool write (std::ostream & file);

private:
	icl::vector <int> code_;
};

