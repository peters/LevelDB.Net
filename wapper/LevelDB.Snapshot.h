#pragma once

#include "db\snapshot.h"

namespace LevelDB
{
	public ref class Snapshot
	{
	private:
		leveldb::DB* db;
	internal:
		const leveldb::Snapshot* snapshot;
	internal:
		Snapshot(leveldb::DB* db);
		~Snapshot(void);
		!Snapshot(void);
	};
}
