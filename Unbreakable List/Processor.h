#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <limits>
#include "Stack.h"

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
	float checkRead (int address, icl::vector <float>* memory);
	void checkWrite (int address, float data, icl::vector <float>* memory);
	

protected:
	icl::vector <MEMCELL> cache_;
	void blockCopy (MEMCELL& cell, int address, icl::vector <float> * memory);
};

class Processor
{
public:
	
	enum comms
	{
		push, pop,
		add, sub, div, mul,
		in, out,
		push_reg, pop_reg,
		push_mem, push_mem_reg, push_mem_reg_add,
		pop_mem, pop_mem_reg, pop_mem_reg_add
	};

	Processor ();
	~Processor ();

	void run (std::ostream & file);
	bool read (std::istream & file);

private:
	icl::stack <float> stack_;
	icl::vector <float> code_;
	icl::vector <float> registers_;
	icl::vector <float> memory_;

	Cache cache_;
};

