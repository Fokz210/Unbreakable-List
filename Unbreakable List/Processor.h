#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <limits>
#include "Stack.h"
#include "DeviceManager.h"


const int CODE_START = 0, CODE_SIZE = 1024,
		  REG_START = CODE_START + CODE_SIZE, REG_SIZE = 6,
		  MEM_START = REG_START + REG_SIZE, MEM_SIZE = 1024,
		  STACK_START = MEM_START + MEM_SIZE, STACK_SIZE = 256;
	

class Cache
{
public:

	class MEMCELL
	{
	public:
		MEMCELL () :
			block_address (-1),
			block (10),
			priority (0)
		{

		}
		
		int block_address;
		icl::vector <float> block;
		int priority;
	};

	Cache ();
	int findUselessIndex ();
	int findCellIndex (int address);
	float checkRead (int address, std::vector <float> * data_);
	void checkWrite (int address, float data, std::vector <float> * data_);
	

protected:
	icl::vector <MEMCELL> cache_;
	void blockCopy (MEMCELL& cell, int address, std::vector <float> *  data);
};

class Processor
{
public:
	
#define DEFCMD(command, num, body)  CMD_##command = num, 

	enum comms
	{
		#include "../Unbreakable List/Commands.h"
	};
	
	#undef DEFCMD

	Processor (DeviceManager PCI);
	~Processor ();

	void run  (std::ostream & file);
	bool read (std::istream & file);

private:
	icl::stack	<int>	callStack_;
	std::vector <float> data_;
	Cache cache_;
	icl::array_based_stack	<float> stack_;
	DeviceManager PCI_;
	int codeSize_;
};

