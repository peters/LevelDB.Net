#pragma once

#include "leveldb/iterator.h"
#include "LevelDB.Slice.h"

namespace LevelDB
{
	public ref class Iterator
	{
	private:
		leveldb::Iterator* iter;
	internal:
		Iterator(leveldb::Iterator* iter);
		~Iterator(void);
		!Iterator(void);
	public:
		Slice Key();
		void Next();
		void Prev();
		void Seek(Slice target);
		void SeekToFirst();
		void SeekToLast();
		bool Valid();
		Slice Value();
	};
}
