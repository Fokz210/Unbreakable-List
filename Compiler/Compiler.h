#pragma once
#include "../Unbreakable List/Stack.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>

class Compiler
{
public:

	struct inscase
	{
		int first;
		std::string second;
	};

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

	bool compile (std::istream & file, bool seciter = false);
	bool write (std::ostream & file);

private:
	icl::vector <int> code_;
	std::map <std::string, int> gt_;
	std::vector <inscase> insertion_;
};

