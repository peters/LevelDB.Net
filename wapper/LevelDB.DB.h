#pragma once

#include "leveldb\db.h"
#include "LevelDB.Iterator.h"
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
	public:
		void Delete(WriteOptions^ options, array<System::Byte>^ key);
		void Delete(WriteOptions^ options, System::String^ key);
		array<System::Byte>^ Get(ReadOptions^ options, array<System::Byte>^ key);
		array<System::Byte>^ Get(ReadOptions^ options, System::String^ key);
		Snapshot^ GetSnapshot();
		System::String^ GetString(ReadOptions^ options, array<System::Byte>^ key);
		System::String^ GetString(ReadOptions^ options, System::String^ key);
		Iterator^ NewIterator(ReadOptions^ options);
		static DB^ Open(System::String^ name);
		void Put(WriteOptions^ options, array<System::Byte>^ key, array<System::Byte>^ value);
		void Put(WriteOptions^ options, array<System::Byte>^ key, System::String^ value);
		void Put(WriteOptions^ options, System::String^ key, array<System::Byte>^ value);
		void Put(WriteOptions^ options, System::String^ key, System::String^ value);
		void Write(WriteOptions^ options, WriteBatch^ write_batch);
	private:
		void DeleteInternal(WriteOptions^ options, leveldb::Slice& key);
		std::string GetInternal(ReadOptions^ options, leveldb::Slice& key);
		void PutInternal(WriteOptions^ options, leveldb::Slice& key, leveldb::Slice& value);
	};
}
