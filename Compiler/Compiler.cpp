#include "Compiler.h"



Compiler::Compiler () :
	code_ ()
{
}


Compiler::~Compiler ()
{
}
	
bool Compiler::compile (std::istream & file)
{
	if (!file)
		return false;

	std::string input;
	comms command;

	while (file >> input)
	{
		if (input == "push")
			command = push;
		else if (input == "add")
			command = add;
		else if (input == "sub")
			command = sub;
		else if (input == "div")
			command = div;
		else if (input == "mul")
			command = mul;
		else if (input == "pop")
			command = pop;
		else
		{
			std::cout << "Compilation error. \"" << input << "\" was not recognised." << std::endl;
			system ("pause");
			return false;
		}

		code_.push_back (command);

		if (command == push)
		{
			int data;
			file >> data;
	
			code_.push_back (data);
		}
		
	}

	return true;
}

bool Compiler::write (std::ostream & file)
{
	if (!file)
		return false;

	for (int i = 0; i < code_.size (); i++)
		file << code_[i] << " ";

	return true;
}
