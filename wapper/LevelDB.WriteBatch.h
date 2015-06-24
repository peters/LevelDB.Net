#pragma once
#pragma warning(disable:4461)

#include "leveldb/write_batch.h"

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
		void Delete(array<System::Byte>^ key);
		void Delete(System::String^ key);
		void Put(array<System::Byte>^ key, array<System::Byte>^ value);
		void Put(array<System::Byte>^ key, System::String^ value);
		void Put(System::String^ key, array<System::Byte>^ value);
		void Put(System::String^ key, System::String^ value);
	};
}
#pragma warning(default:4461)
