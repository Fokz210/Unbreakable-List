#include "../config.h"
#include <cmath>
#include <Windows.h>
#include "Processor.h"

Processor::Processor (DeviceManager PCI) :
	cache_ (),
	callStack_ (),
	data_ (CODE_SIZE + REG_SIZE + MEM_SIZE + STACK_SIZE),
	stack_ (&data_, STACK_SIZE, STACK_START),
	PCI_ (PCI),
	codeSize_ (0)
{
}

Processor::~Processor () 
{
}

void Processor::run (std::ostream & file)
{

	for (unsigned i = CODE_START; i < codeSize_; i++)
	{
		switch (int(data_[i]))
		{

		#define DEFCMD(comm, num, body)  case comms::CMD_##comm:\
										 body \
										 break;												

		#include "Commands.h"

		#undef DEFCMD

		default:
			break;
		}

		PCI_.Run ();
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

	int i = CODE_START;

	while (file >> input)
		data_[i++] = input;

	codeSize_ = i;

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

float Cache::checkRead (int address, std::vector <float> * data_)
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

		float data = (*data_)[address];
		
		blockCopy (cache_[findUselessIndex()], address, data_ );

		return data;
	}
}

void Cache::checkWrite (int address, float data, std::vector <float> *data_)
{
	int cacheCellIndex = -1;
	cacheCellIndex = findCellIndex (address);
	if (cacheCellIndex >= 0)
	{
	Sleep (ICP_CACHE_DELAY);

		cache_[cacheCellIndex].priority++;
		cache_[cacheCellIndex].block[address % 10] = data;

		(*data_)[address] = data;
	}
	else
	{
		Sleep (ICP_MEMORY_DELAY);

		(*data_)[address] = data;
		blockCopy (cache_[findUselessIndex()], address, data_);
	}
}

void Cache::blockCopy (MEMCELL& cell, int address, std::vector <float> * data)
{
	int blockAddress = (address / 10) * 10;

	cell.block.clear ();
	cell.block.resize (10);

	for (int i = blockAddress; i < blockAddress + 10; i++)
		cell.block[i % 10] = (*data)[i];

	cell.block_address = blockAddress;
	cell.priority = 0;
}
