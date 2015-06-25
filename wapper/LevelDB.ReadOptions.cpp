#include "LevelDB.ReadOptions.h"

using namespace LevelDB;

ReadOptions::ReadOptions(void)
{
	this->VerifyChecksums = false;
	this->FillCache = true;
	this->Snapshot = nullptr;
}

leveldb::ReadOptions ReadOptions::ToUnmanaged()
{
	leveldb::ReadOptions options;
	options.verify_checksums = VerifyChecksums;
	options.fill_cache = FillCache;
	options.snapshot = Snapshot == nullptr ? nullptr : Snapshot->snapshot;
	return options;
}
