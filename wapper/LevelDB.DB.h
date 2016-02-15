#pragma once

#include "leveldb\db.h"
#include "LevelDB.Iterator.h"
#include "LevelDB.Options.h"
#include "LevelDB.ReadOptions.h"
#include "LevelDB.WriteBatch.h"
#include "LevelDB.WriteOptions.h"

namespace LevelDB
{
	public ref class DB
	{
	private:
		leveldb::DB* db_inner;
	private:
		DB(leveldb::DB* db_inner);
		~DB(void);
		!DB(void);
	public:
		void Delete(WriteOptions^ options, Slice key);
		Slice Get(ReadOptions^ options, Slice key);
		Snapshot^ GetSnapshot();
		Iterator^ NewIterator(ReadOptions^ options);
		static DB^ Open(System::String^ name);
		static DB^ Open(System::String^ name, Options^ options);
		void Put(WriteOptions^ options, Slice key, Slice value);
		bool TryGet(ReadOptions^ options, Slice key, [System::Runtime::InteropServices::Out] Slice% value);
		void Write(WriteOptions^ options, WriteBatch^ write_batch);
	};
}
