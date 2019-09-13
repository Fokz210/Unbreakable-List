#include "../config.h"
#include "Compiler.h"

Compiler::Compiler () :
	code_ ()
{
}

Compiler::~Compiler ()
{
}
	
bool Compiler::compile (std::istream & file, bool seciter)
{

	std::streampos start = file.tellg ();

	std::string input;
	comms command;

	while (file >> input)
	{

		#define DEFCMD(comm, num, body)  else if (input == #comm) \
										command = CMD_##comm; 
		if (0);
		#include "../Unbreakable List/Commands.h"
		else if (input[input.size () - 1] == ':')
		{
			input.pop_back ();
			gt_.insert (std::pair <std::string, int> (input, code_.size ()));
			continue;
		}
		else
		{
			std::cout << "Compilation error. \"" << input << "\" was not recognised." << std::endl;
			system ("pause");
			return false;
		}

		#undef DEFCMD

		if (command == CMD_IN || command == CMD_OUT || command == CMD_SLEEP)
		{
			file >> input;
			code_.push_back (command);
			code_.push_back (std::stoi (input));
		}
		else if (command >= CMD_JMP && command <= CMD_CALL)
		{
			file >> input;
			code_.push_back (command);
			
			if (input[0] >= '0' && input[0] <= '9')
				code_.push_back (std::stoi (input));
			else
			{
				if (gt_.find (input) != gt_.end ())
					code_.push_back (gt_[input]);
				else
				{
					insertion_.push_back ({ (int)code_.size (), input });
					code_.push_back (0);
				}
			}
		}
		else if (command == CMD_PUSH)
		{
			file >> input;

			if (input == "AX")
			{
				code_.push_back (CMD_PUSH_REG);
				code_.push_back (REG_AX);
			}
			else if (input == "BX")
			{
				code_.push_back (CMD_PUSH_REG);
				code_.push_back (REG_BX);
			}
			else if (input == "CX")
			{
				code_.push_back (CMD_PUSH_REG);
				code_.push_back (REG_CX);
			}
			else if (input == "DX")
			{
				code_.push_back (CMD_PUSH_REG);
				code_.push_back (REG_DX);
			}
			else if (input == "BP")
			{
				code_.push_back (CMD_PUSH_REG);
				code_.push_back (REG_BP);
			}
			else if (input == "SP");
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
					else if (iterator == "SP");
					else if (iterator == "BP")
					{
						code_.push_back (CMD_PUSH_MEM_REG);
						code_.push_back (REG_BP);
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
					else if (iterator == "SP");
					else if (iterator == "BP")
					{
						code_.push_back (CMD_PUSH_MEM_REG_ADD);
						code_.push_back (REG_BP);
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
			else if (input == "SP")
			{
				code_.push_back (CMD_GETSP);
			}
			else if (input == "BP")
			{
				code_.push_back (CMD_POP_REG);
				code_.push_back (REG_BP);
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
					else if (iterator == "SP");
					else if (iterator == "BP")
					{
						code_.push_back (CMD_POP_MEM_REG);
						code_.push_back (REG_BP);
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
					else if (iterator == "SP");
					else if (iterator == "BP")
					{
						code_.push_back (CMD_POP_MEM_REG_ADD);
						code_.push_back (REG_BP);
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

	for (int i = 0; i < insertion_.size (); i++)
	{
		code_[insertion_[i].first] = gt_[insertion_[i].second];
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
