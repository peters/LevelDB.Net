#pragma once
#pragma warning(disable:4461)

#include "leveldb/write_batch.h"
#include "LevelDB.Slice.h"

namespace LevelDB
{
	public ref class WriteBatch
	{
	internal:
		leveldb::WriteBatch* write_batch;
	public:
		WriteBatch(void);
		!WriteBatch(void);
	public:
		void Clear();
		void Delete(Slice key);
		void Put(Slice key, Slice value);
	};
}
#pragma warning(default:4461)
