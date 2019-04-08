#include "Processor.h"



Processor::Processor () :
	stack_ (),
	code_ ()
{
}


Processor::~Processor () 
{
}

void Processor::run (std::ostream & file)
{
	for (int i = 0; i < code_.size (); i++)
	{
		switch (code_[i].command)
		{
		case Processor::push:
		{
			stack_.push (code_[i].input);
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
		case Processor::pop:
		{
			file << stack_.pop () << std::endl;
		}
		break;
		default:
			break;
		}
	}
}

void Processor::read (std::istream & file)
{
	int input;

	while (file >> input)
	{

		int data = 0;

		if (input == push)
			file >> data;

		code_.push_back ({ (comms) input, data });
	}
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
