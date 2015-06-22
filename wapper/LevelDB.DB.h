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
		array<System::Byte>^ Get(array<System::Byte>^ key);
		static DB^ Open(System::String^ name);
		void Put(array<System::Byte>^ key, array<System::Byte>^ value);
	};
}
