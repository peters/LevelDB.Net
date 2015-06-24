#pragma once

#include "leveldb/iterator.h"

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
		array<System::Byte>^ Key();
		System::String^ KeyAsString();
		void Next();
		void Prev();
		void Seek(array<System::Byte>^ target);
		void Seek(System::String^ target);
		void SeekToFirst();
		void SeekToLast();
		bool Valid();
		array<System::Byte>^ Value();
		System::String^ ValueAsString();
	};
}
