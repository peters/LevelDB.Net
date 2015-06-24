#pragma once

#include "LevelDB.Snapshot.h"

namespace LevelDB
{
	public ref class ReadOptions
	{
	public:
		static initonly ReadOptions^ Default = gcnew ReadOptions();
	public:
		property bool VerifyChecksums;
		property bool FillCache;
		property Snapshot^ Snapshot;
	public:
		ReadOptions(void);
	internal:
		leveldb::ReadOptions ToUnmanaged();
	};
}
