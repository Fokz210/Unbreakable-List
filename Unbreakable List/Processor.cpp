#include "../config.h"
#include <cmath>
#include <Windows.h>
#include "Processor.h"


Processor::Processor () :
	stack_ (),
	code_ (),
	registers_ (5),
	memory_ (1024),
	cache_ ()
{
}

Processor::~Processor () 
{
}

void Processor::run (std::ostream & file)
{
	for (unsigned i = 0; i < code_.size (); i++)
	{
		switch (int(code_[i]))
		{

		#define DEFCMD(comm, num, body)  case CMD_##comm:\
										 body \
										 break;													

		#include "Commands.h"

		#undef DEFCMD

		default:
			break;
		}

	}
}

bool Processor::read (std::istream & file)
{
	FileHeader header;

	int sig, ver;

	file >> sig >> ver;

	if (sig != header.signature || ver != header.version)
	{
		std::cout << "Depricated syntax, please update file.\n";
		return false;
	}

	int input;

	while (file >> input)
		code_.push_back (input);

	return true;
}

//void Processor::parse ()
//{
//	std::string input;
//	std::cin >> input;
//
//	comms command;
//
//	if (input == "push")
//		command = push;
//	else if (input == "add")
//		command = add;
//	else if (input == "sub")
//		command = sub;
//	else if (input == "div")
//		command = div;
//	else if (input == "mul")
//		command = mul;
//	else if (input == "pop")
//		command = pop;
//	else
//	{
//		std::cout << "Sorry, didn't chatch that." << std::endl;
//	}
//
//	switch (command)
//	{
//	case Processor::push:
//	{
//		int num;
//		std::cin >> num;
//
//		stack_.push (num); 
//	}
//		break;
//	case Processor::add:
//	{
//		int a = stack_.pop (), b = stack_.pop ();
//		stack_.push (a + b);
//	}
//		break;
//	case Processor::sub:
//	{
//		int a = stack_.pop (), b = stack_.pop ();
//		stack_.push (a - b);
//	}
//		break;
//	case Processor::div:
//	{
//		int a = stack_.pop (), b = stack_.pop ();
//		stack_.push (a / b);
//	}
//		break;
//	case Processor::mul:
//	{
//		int a = stack_.pop (), b = stack_.pop ();
//		stack_.push (a * b);
//	}
//		break;
//	case Processor::pop:
//	{
//		std::cout << stack_.pop () << std::endl;
//	}
//		break;
//	default:
//		break;
//	}
//}

Cache::Cache () :
	cache_ (128)
{
}

int Cache::findUselessIndex ()
{
	int lowestPriority = INT_MAX;
	int useless = 0;

	for (int i = 0; i < cache_.size (); i++)
		if (cache_[i].priority < lowestPriority)
			useless = i;

	return useless;
}

int Cache::findCellIndex (int address)
{
	int blockAdress = (address / 10) * 10;

	for (int i = 0; i < cache_.size (); i++)
		if (cache_[i].block_address == blockAdress)
			return i;

	return -1;
}

float Cache::checkRead (int address, icl::vector<float>* memory)
{
	int cacheCellIndex = -1;
	cacheCellIndex = findCellIndex (address);


	if (cacheCellIndex >= 0)
	{
		Sleep (ICP_CACHE_DELAY);

		cache_[cacheCellIndex].priority++;

		return cache_[cacheCellIndex].block[address % 10];
	}
	else
	{
		Sleep (ICP_MEMORY_DELAY);

		float data = (*memory)[address];
		
		blockCopy (cache_[findUselessIndex()], address, memory);

		return data;
	}
}

void Cache::checkWrite (int address, float data, icl::vector<float>* memory)
{
	int cacheCellIndex = -1;
	cacheCellIndex = findCellIndex (address);
	if (cacheCellIndex >= 0)
	{
	Sleep (ICP_CACHE_DELAY);

		cache_[cacheCellIndex].priority++;
		cache_[cacheCellIndex].block[address % 10] = data;

		(*memory)[address] = data;
	}
	else
	{
		Sleep (ICP_MEMORY_DELAY);

		(*memory)[address] = data;
		blockCopy (cache_[findUselessIndex()], address, memory);
	}
}

void Cache::blockCopy (MEMCELL& cell, int address, icl::vector<float>* memory)
{
	int blockAddress = (address / 10) * 10;

	cell.block.clear ();
	cell.block.resize (10);

	for (int i = blockAddress; i < blockAddress + 10; i++)
		cell.block[i % 10] = (*memory)[i];

	cell.block_address = blockAddress;
	cell.priority = 0;
}
