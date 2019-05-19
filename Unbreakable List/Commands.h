#ifdef DEFCMD

#define _PUSH  stack_.push 
#define _POP   stack_.pop ()

DEFCMD (NOP, 0, {})

DEFCMD (PUSH, 1,
	{
		_PUSH (code_[++i]);
	})

DEFCMD (POP, 2, 
	{
		file << _POP;
	})

DEFCMD (ADD, 3,
	{
		float a = _POP, b = _POP;
		_PUSH (b + a);
	})

DEFCMD (SUB, 4,
	{
		float a = _POP, b = _POP;
		_PUSH (b - a);
	})

DEFCMD (DIV, 5,
	{
		float a = _POP, b = _POP;
		_PUSH (b / a);
	})

DEFCMD (MUL, 6,
	{
		float a = _POP, b = _POP;
		_PUSH (b * a);
	})

DEFCMD (IN, 7,
	{
		float input = 0;
		std::cin >> input;
		_PUSH (input);
	})

DEFCMD (OUT, 8,
	{
		float output = _POP;
		std::cout << output << "\n";
	})

DEFCMD (PUSH_REG, 9, 
	{
		registers_[code_[++i]] = _POP;
	})

DEFCMD (POP_REG, 10,
	{
		_PUSH (registers_[code_[++i]]);
	})
	
DEFCMD (PUSH_MEM, 11,
	{
		cache_.checkWrite (code_[++i], _POP, &memory_);
	})

DEFCMD (PUSH_MEM_REG, 12,
	{
		cache_.checkWrite (registers_[code_[++i]], _POP, &memory_);
	})

DEFCMD (PUSH_MEM_REG_ADD, 13,
	{
		cache_.checkWrite (registers_[code_[++i]] + code_[++i], _POP, &memory_);
	})

DEFCMD (POP_MEM, 14,
	{
		_PUSH (cache_.checkRead (code_[++i], &memory_));
	})

DEFCMD (POP_MEM_REG, 15,
	{
		_PUSH (cache_.checkRead (registers_[code_[++i]], &memory_));
	})

DEFCMD (POP_MEM_REG_ADD, 16,
	{
		_PUSH (cache_.checkRead (registers_[code_[++i]] + code_[++i], &memory_));
	})

DEFCMD (SQRT, 17,
	{
		_PUSH (sqrt (_POP));
	})
#endif

#ifdef DEFREG
DEFREG (UNDEF, 0)
DEFREG (AX, 1)
DEFREG (BX, 2)
DEFREG (CX, 3)
DEFREG (DX, 4)
#endif
