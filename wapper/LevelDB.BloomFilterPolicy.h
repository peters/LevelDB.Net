#pragma once

#include "LevelDB.FilterPolicy.h"

namespace LevelDB
{
	public ref class BloomFilterPolicy : public FilterPolicy
	{
	public:
		BloomFilterPolicy(int bits_per_key);
		~BloomFilterPolicy(void);
		!BloomFilterPolicy(void);
	};
}
