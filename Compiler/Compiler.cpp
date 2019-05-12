#include "../config.h"
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
		else if (input == "in")
			command = in;
		else if (input == "out")
			command = out;
		else
		{
			std::cout << "Compilation error. \"" << input << "\" was not recognised." << std::endl;
			system ("pause");
			return false;
		}

		if (command == push)
		{
			file >> input;

			if (input == "ax")
			{
				code_.push_back (push_reg);
				code_.push_back (ax);
			}
			else if (input == "bx")
			{
				code_.push_back (push_reg);
				code_.push_back (bx);
			}
			else if (input == "cx")
			{
				code_.push_back (push_reg);
				code_.push_back (cx);
			}
			else if (input == "dx")
			{
				code_.push_back (push_reg);
				code_.push_back (dx);
			}
			else if (input[0] == '[')
			{
				if (input[input.size () - 1] == ']')
				{
					std::string iterator = input.substr (1, input.size () - 2);
					
					if (iterator == "ax")
					{
						code_.push_back (push_mem_reg);
						code_.push_back (ax);
					}
					else if (iterator == "bx")
					{
						code_.push_back (push_mem_reg);
						code_.push_back (bx);
					}
					else if (iterator == "cx")
					{
						code_.push_back (push_mem_reg);
						code_.push_back (cx);
					}
					else if (iterator == "dx")
					{
						code_.push_back (push_mem_reg);
						code_.push_back (dx);
					}
					else
					{
						code_.push_back (push_mem);
						code_.push_back (std::stoi (iterator));
					}
				}
				else
				{
					std::string iterator = input.substr (1);

					if (iterator == "ax")
					{
						code_.push_back (push_mem_reg_add);
						code_.push_back (ax);
					}
					else if (iterator == "bx")
					{
						code_.push_back (push_mem_reg_add);
						code_.push_back (bx);
					}
					else if (iterator == "cx")
					{
						code_.push_back (push_mem_reg_add);
						code_.push_back (cx);
					}
					else if (iterator == "dx")
					{
						code_.push_back (push_mem_reg_add);
						code_.push_back (dx);
					}

					file >> input >> input;

					input.pop_back ();

					code_.push_back (std::stoi (input));
				}
			}
			else
			{
				code_.push_back (push);
				code_.push_back (std::stoi (input));
			}

		}
		else if (command == pop)
		{
			std::streampos currPos = file.tellg ();

			file >> input;

			if (input == "ax")
			{
				code_.push_back (pop_reg);
				code_.push_back (ax);
			}
			else if (input == "bx")
			{
				code_.push_back (pop_reg);
				code_.push_back (bx);
			}
			else if (input == "cx")
			{
				code_.push_back (pop_reg);
				code_.push_back (cx);
			}
			else if (input == "dx")
			{
				code_.push_back (pop_reg);
				code_.push_back (dx);
			}
			else if (input[0] == '[')
			{
				if (input[input.size () - 1] == ']')
				{
					std::string iterator = input.substr (1, input.size () - 2);

					if (iterator == "ax")
					{
						code_.push_back (pop_mem_reg);
						code_.push_back (ax);
					}
					else if (iterator == "bx")
					{
						code_.push_back (pop_mem_reg);
						code_.push_back (bx);
					}
					else if (iterator == "cx")
					{
						code_.push_back (pop_mem_reg);
						code_.push_back (cx);
					}
					else if (iterator == "dx")
					{
						code_.push_back (pop_mem_reg);
						code_.push_back (dx);
					}
					else
					{
						code_.push_back (pop_mem);
						code_.push_back (std::stoi (iterator));
					}
				}
				else
				{
					std::string iterator = input.substr (1);

					if (iterator == "ax")
					{
						code_.push_back (pop_mem_reg_add);
						code_.push_back (ax);
					}
					else if (iterator == "bx")
					{
						code_.push_back (pop_mem_reg_add);
						code_.push_back (bx);
					}
					else if (iterator == "cx")
					{
						code_.push_back (pop_mem_reg_add);
						code_.push_back (cx);
					}
					else if (iterator == "dx")
					{
						code_.push_back (pop_mem_reg_add);
						code_.push_back (dx);
					}

					file >> input >> input;

					input.pop_back ();

					code_.push_back (std::stoi (input));
				}
			}
			else
			{
				file.seekg (currPos);
				code_.push_back (pop);
			}
		}
		else 
			code_.push_back (command);
	}


	return true;
}

bool Compiler::write (std::ostream & file)
{
	if (!file)
		return false;

	FileHeader header;

	file << header.signature << " " << header.version << " ";

	for (unsigned i = 0; i < code_.size (); i++)
		file << code_[i] << " ";

	return true;
}
