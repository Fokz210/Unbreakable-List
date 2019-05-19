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
		
		#define DEFCMD(comm, num)  else if (input == #comm) \
										command = CMD_##comm; 
		if (0);
		#include "../Unbreakable List/Commands.h"
	    else
		{
			std::cout << "Compilation error. \"" << input << "\" was not recognised." << std::endl;
			system ("pause");
			return false;
		}

		#undef DEFCMD

		if (command == CMD_PUSH)
		{
			file >> input;

			if (input == "AX")
			{
				code_.push_back (CMD_PUSH_MEM);
				code_.push_back (REG_AX);
			}
			else if (input == "BX")
			{
				code_.push_back (CMD_PUSH_MEM);
				code_.push_back (REG_BX);
			}
			else if (input == "CX")
			{
				code_.push_back (CMD_PUSH_MEM);
				code_.push_back (REG_CX);
			}
			else if (input == "DX")
			{
				code_.push_back (CMD_PUSH_MEM);
				code_.push_back (REG_DX);
			}
			else if (input[0] == '[')
			{
				if (input[input.size () - 1] == ']')
				{
					std::string iterator = input.substr (1, input.size () - 2);
					
					if (iterator == "AX")
					{
						code_.push_back (CMD_PUSH_MEM_REG);
						code_.push_back (REG_AX);
					}
					else if (iterator == "BX")
					{
						code_.push_back (CMD_PUSH_MEM_REG);
						code_.push_back (REG_BX);
					}
					else if (iterator == "CX")
					{
						code_.push_back (CMD_PUSH_MEM_REG);
						code_.push_back (REG_CX);
					}
					else if (iterator == "DX")
					{
						code_.push_back (CMD_PUSH_MEM_REG);
						code_.push_back (REG_DX);
					}
					else
					{
						code_.push_back (CMD_PUSH_MEM);
						code_.push_back (std::stoi (iterator));
					}
				}
				else
				{
					std::string iterator = input.substr (1);

					if (iterator == "AX")
					{
						code_.push_back (CMD_PUSH_MEM_REG_ADD);
						code_.push_back (REG_AX);
					}
					else if (iterator == "BX")
					{
						code_.push_back (CMD_PUSH_MEM_REG_ADD);
						code_.push_back (REG_BX);
					}
					else if (iterator == "CX")
					{
						code_.push_back (CMD_PUSH_MEM_REG_ADD);
						code_.push_back (REG_CX);
					}
					else if (iterator == "DX")
					{
						code_.push_back (CMD_PUSH_MEM_REG_ADD);
						code_.push_back (REG_DX);
					}

					file >> input >> input;

					input.pop_back ();

					code_.push_back (std::stoi (input));
				}
			}
			else
			{
				code_.push_back (CMD_PUSH);
				code_.push_back (std::stoi (input));
			}

		}
		else if (command == CMD_POP)
		{
			std::streampos currPos = file.tellg ();

			file >> input;

			if (input == "AX")
			{
				code_.push_back (CMD_POP_REG);
				code_.push_back (REG_AX);
			}
			else if (input == "BX")
			{
				code_.push_back (CMD_POP_REG);
				code_.push_back (REG_BX);
			}
			else if (input == "CX")
			{
				code_.push_back (CMD_POP_REG);
				code_.push_back (REG_CX);
			}
			else if (input == "DX")
			{
				code_.push_back (CMD_POP_REG);
				code_.push_back (REG_DX);
			}
			else if (input[0] == '[')
			{
				if (input[input.size () - 1] == ']')
				{
					std::string iterator = input.substr (1, input.size () - 2);

					if (iterator == "AX")
					{
						code_.push_back (CMD_POP_MEM_REG);
						code_.push_back (REG_AX);
					}
					else if (iterator == "BX")
					{
						code_.push_back (CMD_POP_MEM_REG);
						code_.push_back (REG_BX);
					}
					else if (iterator == "CX")
					{
						code_.push_back (CMD_POP_MEM_REG);
						code_.push_back (REG_CX);
					}
					else if (iterator == "DX")
					{
						code_.push_back (CMD_POP_MEM_REG);
						code_.push_back (REG_DX);
					}
					else
					{
						code_.push_back (CMD_POP_REG);
						code_.push_back (std::stoi (iterator));
					}
				}
				else
				{
					std::string iterator = input.substr (1);

					if (iterator == "AX")
					{
						code_.push_back (CMD_POP_MEM_REG_ADD);
						code_.push_back (REG_AX);
					}
					else if (iterator == "BX")
					{
						code_.push_back (CMD_POP_MEM_REG_ADD);
						code_.push_back (REG_BX);
					}
					else if (iterator == "CX")
					{
						code_.push_back (CMD_POP_MEM_REG_ADD);
						code_.push_back (REG_CX);
					}
					else if (iterator == "DX")
					{
						code_.push_back (CMD_POP_MEM_REG_ADD);
						code_.push_back (REG_DX);
					}

					file >> input >> input;

					input.pop_back ();

					code_.push_back (std::stoi (input));
				}
			}
			else
			{
				file.seekg (currPos);
				code_.push_back (CMD_POP);
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
