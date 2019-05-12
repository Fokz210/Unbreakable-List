#include "../config.h"
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
		case Processor::push:
		{
			stack_.push (code_[++i]);
		}
		break;

		case Processor::pop:
		{
			file << stack_.pop ();
		}
		break;

		case Processor::push_reg:
		{
			registers_[code_[++i]] = stack_.pop ();
		}
		break;

		case Processor::add:
		{
			float a = stack_.pop (), b = stack_.pop ();
			stack_.push (b + a);
		}
		break;

		case Processor::sub:
		{
			float a = stack_.pop (), b = stack_.pop ();
			stack_.push (b - a);
		}
		break;

		case Processor::div:
		{
			float a = stack_.pop (), b = stack_.pop ();
			stack_.push (b / a);
		}
		break;

		case Processor::mul:
		{
			float a = stack_.pop (), b = stack_.pop ();
			stack_.push (b * a);
		}
		break;

		case Processor::pop_reg:
		{
			stack_.push (registers_[code_[++i]]);
		}
		break;

		case Processor::in:
		{
			float input = 0;
			std::cin >> input;
			stack_.push (input);
		}
		break;

		case Processor::out:
		{
			float output = stack_.pop ();
			std::cout << output << "\n";
		}
		break;

		case Processor::push_mem:
		{
			cache_.checkWrite (code_[++i], stack_.pop (), &memory_);
		}
		break;

		case Processor::push_mem_reg:
		{
			cache_.checkWrite (registers_[code_[++i]], stack_.pop (), &memory_);
		}
		break;

		case Processor::push_mem_reg_add:
		{
			cache_.checkWrite (registers_[code_[++i]] + code_[++i], stack_.pop (), &memory_);
		}
		break;

		case Processor::pop_mem:
		{
			stack_.push (cache_.checkRead (code_[++i], &memory_));
		}
		break;

		case Processor::pop_mem_reg:
		{
			stack_.push (cache_.checkRead (registers_[code_[++i]], &memory_));
		}
		break;
		
		case Processor::pop_mem_reg_add:
		{
			stack_.push (cache_.checkRead (registers_[code_[++i]] + code_[++i], &memory_));
		}
		break;

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
