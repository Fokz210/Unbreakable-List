#pragma once

#define ICP_MEMORY_DELAY 100

struct FileHeader
{
	int signature = 'IC', version = 3;
};
