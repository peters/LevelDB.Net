#include "LevelDB.BloomFilterPolicy.h"

using namespace LevelDB;

BloomFilterPolicy::BloomFilterPolicy(int bits_per_key)
{
	this->policy = leveldb::NewBloomFilterPolicy(bits_per_key);
}

BloomFilterPolicy::~BloomFilterPolicy(void)
{
	this->!BloomFilterPolicy();
}

BloomFilterPolicy::!BloomFilterPolicy(void)
{
	if (policy != nullptr)
	{
		delete policy;
		policy = nullptr;
	}
}
