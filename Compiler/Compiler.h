#pragma once
#include "../Unbreakable List/Stack.h"
#include <iostream>
#include <string>

class Compiler
{
public:

	#define DEFREG(reg, num)  REG_##reg = num,

	enum regs
	{
		#include "../Unbreakable List/Commands.h"
	};

	#undef DEFREG

	#define DEFCMD(command, num, data)  CMD_##command = num, 

	enum comms
	{
		#include "../Unbreakable List/Commands.h"
	};

	#undef DEFCMD

	Compiler ();
	~Compiler ();

	bool compile (std::istream & file);
	bool write (std::ostream & file);

private:
	icl::vector <int> code_;
};

