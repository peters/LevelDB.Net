#include "LevelDB.WriteOptions.h"

using namespace LevelDB;

WriteOptions::WriteOptions(void)
{
	this->Sync = false;
}

leveldb::WriteOptions WriteOptions::ToUnmanaged()
{
	leveldb::WriteOptions options;
	options.sync = Sync;
	return options;
}
