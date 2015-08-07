#include "LevelDB.Snapshot.h"

using namespace LevelDB;

Snapshot::Snapshot(leveldb::DB* db)
	:db(db),
	snapshot(db->GetSnapshot())
{
}

Snapshot::~Snapshot(void)
{
	this->!Snapshot();
}

Snapshot::!Snapshot(void)
{
	if (snapshot != nullptr)
	{
		db->ReleaseSnapshot(snapshot);
		snapshot = nullptr;
	}
}
