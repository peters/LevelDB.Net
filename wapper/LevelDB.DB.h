#pragma once

#include "leveldb\db.h"

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
		void Delete(array<System::Byte>^ key);
		void Delete(System::String^ key);
		array<System::Byte>^ Get(array<System::Byte>^ key);
		array<System::Byte>^ Get(System::String^ key);
		System::String^ GetString(array<System::Byte>^ key);
		System::String^ GetString(System::String^ key);
		static DB^ Open(System::String^ name);
		void Put(array<System::Byte>^ key, array<System::Byte>^ value);
		void Put(array<System::Byte>^ key, System::String^ value);
		void Put(System::String^ key, array<System::Byte>^ value);
		void Put(System::String^ key, System::String^ value);
	private:
		void DeleteInternal(leveldb::Slice& key);
		std::string GetInternal(leveldb::Slice& key);
		void PutInternal(leveldb::Slice& key, leveldb::Slice& value);
	};
}
