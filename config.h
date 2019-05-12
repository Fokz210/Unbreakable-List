#pragma once

#define ICP_MEMORY_DELAY 10000
#define ICP_CACHE_DELAY  500

struct FileHeader
{
	int signature = 'IC', version = 4;
};
