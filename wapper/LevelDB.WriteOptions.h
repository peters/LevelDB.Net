#pragma once

#include "leveldb\options.h"

namespace LevelDB
{
	public ref class WriteOptions
	{
	public:
		static initonly WriteOptions^ Default = gcnew WriteOptions();
	public:
		property bool Sync;
	public:
		WriteOptions(void);
	internal:
		leveldb::WriteOptions ToUnmanaged();
	};
}
