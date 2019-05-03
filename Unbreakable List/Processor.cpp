#include "../config.h"
#include <Windows.h>
#include "Processor.h"


Processor::Processor () :
	stack_ (),
	code_ (),
	registers_ (5),
	memory_ (1024)
{
}

Processor::~Processor () 
{
}

void Processor::run (std::ostream & file)
{
	for (int i = 0; i < code_.size (); i++)
	{
		switch (code_[i])
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
			int a = stack_.pop (), b = stack_.pop ();
			stack_.push (a + b);
		}
		break;

		case Processor::sub:
		{
			int a = stack_.pop (), b = stack_.pop ();
			stack_.push (a - b);
		}
		break;

		case Processor::div:
		{
			int a = stack_.pop (), b = stack_.pop ();
			stack_.push (a / b);
		}
		break;

		case Processor::mul:
		{
			int a = stack_.pop (), b = stack_.pop ();
			stack_.push (a * b);
		}
		break;

		case Processor::pop_reg:
		{
			stack_.push (registers_[code_[++i]]);
		}
		break;

		case Processor::in:
		{
			int input = 0;
			std::cin >> input;
			stack_.push (input);
		}
		break;

		case Processor::out:
		{
			int output = stack_.pop ();
			std::cout << output << "\n";
		}
		break;

		case Processor::push_mem:
		{
			memory_[code_[++i]] = stack_.pop ();
			Sleep (ICP_MEMORY_DELAY);
		}
		break;

		case Processor::push_mem_reg:
		{
			memory_[registers_[code_[++i]]] = stack_.pop ();
			Sleep (ICP_MEMORY_DELAY);
		}
		break;

		case Processor::push_mem_reg_add:
		{
			memory_[registers_[code_[++i]] + code_[++i]] = stack_.pop ();
			Sleep (ICP_MEMORY_DELAY);
		}
		break;

		case Processor::pop_mem:
		{
			stack_.push (memory_[code_[++i]]);
			Sleep (ICP_MEMORY_DELAY);
		}
		break;

		case Processor::pop_mem_reg:
		{
			stack_.push (memory_[registers_[code_[++i]]]);
			Sleep (ICP_MEMORY_DELAY);
		}
		break;
		
		case Processor::pop_mem_reg_add:
		{
			stack_.push (memory_[registers_[code_[++i]] + code_[++i]]);
			Sleep (ICP_MEMORY_DELAY);
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
