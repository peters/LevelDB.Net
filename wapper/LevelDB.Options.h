#pragma once

#include "LevelDB.CompressionType.h"
#include "LevelDB.FilterPolicy.h"

namespace LevelDB
{
	public ref class Options
	{
	public:
		static initonly Options^ Default = gcnew Options();
	public:
		bool CreateIfMissing;
		bool ErrorIfExists;
		bool ParanoidChecks;
		size_t WriteBufferSize;
		int MaxOpenFiles;
		size_t BlockSize;
		int BlockRestartInterval;
		CompressionType Compression;
		FilterPolicy^ FilterPolicy;
	public:
		Options(void);
	internal:
		leveldb::Options ToUnmanaged();
	};
}
