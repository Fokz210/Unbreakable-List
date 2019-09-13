#ifdef DEFCMD

#define _PUSH  stack_.push 
#define _POP   stack_.pop ()
#define _JUMP  i = iter - 1

#define _  ,

DEFCMD (NOP, 0, {})

DEFCMD (PUSH, 1,
	{
		_PUSH (data_[++i]);
	})

DEFCMD (POP, 2, 
	{
		_POP;
	})

DEFCMD (ADD, 3,
	{
		float a = _POP _ b = _POP;
		_PUSH (b + a);
	})

DEFCMD (SUB, 4,
	{
		float a = _POP _ b = _POP;
		_PUSH (b - a);
	})

DEFCMD (DIV, 5,
	{
		float a = _POP _ b = _POP;
		_PUSH (b / a);
	})

DEFCMD (MUL, 6,
	{
		float a = _POP _ b = _POP;
		_PUSH (b * a);
	})

#undef IN
#undef OUT
		
DEFCMD (IN, 28,
	{
		int port = data_ [++i];		
		_PUSH (PCI_.Out (port));
	})

DEFCMD (OUT, 29,
	{
		int port = data_[++i];
		PCI_.In (port _ _POP);
	})

#define IN
#define OUT

DEFCMD (PUSH_REG, 9, 
	{
		std::cout << REG_START + (int)data_[i + 1] << "\n";
		data_[REG_START + (int)data_[++i]] = _POP;
		std::cout << data_[REG_START + (int)data_[i]] << "\n";
	})

DEFCMD (POP_REG, 10,
	{
		_PUSH (data_[REG_START + (int)data_[++i]]);
	})
	
DEFCMD (PUSH_MEM, 11,
	{
		cache_.checkWrite (data_[++i], _POP, &data_);
	})

DEFCMD (PUSH_MEM_REG, 12,
	{
		cache_.checkWrite (data_[REG_START + (int)data_[++i]], _POP, &data_);
	})

DEFCMD (PUSH_MEM_REG_ADD, 13,
	{
		cache_.checkWrite (data_[REG_START + (int)data_[i + 1]] + data_[i + 2], _POP, &data_);

		i += 2;
	})

DEFCMD (POP_MEM, 14,
	{
		_PUSH (cache_.checkRead (data_[++i], &data_));
	})

DEFCMD (POP_MEM_REG, 15,
	{
		_PUSH (cache_.checkRead (data_[REG_START + (int)data_[++i]], &data_));
	})

DEFCMD (POP_MEM_REG_ADD, 16,
	{
		
		_PUSH (cache_.checkRead (data_[REG_START + (int)data_[i + 1]] + data_[i + 2], &data_));
	    i += 2;
	})

DEFCMD (SQRT, 17,
	{
		_PUSH (sqrt (_POP));
	})

DEFCMD (JMP, 18,
	{
		i = data_[++i] - 1;
	})

DEFCMD (JA, 19,
	{
		float a = _POP _ b = _POP;
		int iter = data_[++i];
		if (b > a)
			_JUMP;
	})

DEFCMD (JAE, 20, 
	{
		float a = _POP _ b = _POP;
		int iter = data_[++i];
		if (b >= a)
			_JUMP;
	})

DEFCMD (JB, 21, 
	{
		float a = _POP _ b = _POP;
		int iter = data_[++i];
		if (b < a)
			_JUMP;
	})

DEFCMD (JBE, 22, 
	{
		float a = _POP _ b = _POP;
		int iter = data_[++i];
		if (b <= a)
			_JUMP;
	})

DEFCMD (JE, 23,
	{
		float a = _POP _ b = _POP;
		int iter = data_[++i];
		if (b == a)
			_JUMP;
	})

DEFCMD (JNE, 24,
	{
		float a = _POP _ b = _POP;
		int iter = data_[++i];
		if (b != a)
			_JUMP;
	})

DEFCMD (CALL, 25,
	{
		stack_.push (i + 2);
		int iter = data_[++i];
		_JUMP;
	})

DEFCMD (RET, 26,
	{
		int iter = stack_.pop();
		_JUMP;
	})

DEFCMD (GETSP, 27, 
	{
		_PUSH (STACK_START + stack_.size () - 1);
	})

DEFCMD (CIN, 7,
	{
		float input = 0;
		std::cin >> input;
		_PUSH (input);
	})

DEFCMD (COUT, 8,
	{
		float output = _POP;
		std::cout << output << "\n";
	})

DEFCMD (SLEEP, 30,
	{
		Sleep (data_[++i]);
	})


#endif

#ifdef DEFREG
DEFREG (UNDEF, 0)
DEFREG (AX, 1)
DEFREG (BX, 2)
DEFREG (CX, 3)
DEFREG (DX, 4)
DEFREG (BP, 5)
#endif
