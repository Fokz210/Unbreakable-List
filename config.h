#pragma once

#define ICP_MEMORY_DELAY 1//0000
#define ICP_CACHE_DELAY  5//00

struct FileHeader
{
	int signature = 'IC', version = 4;
};
