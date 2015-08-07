#pragma once

#include "leveldb/options.h"

namespace LevelDB
{
	public enum class CompressionType
	{
		NoCompression = leveldb::CompressionType::kNoCompression,
		SnappyCompression = leveldb::CompressionType::kSnappyCompression
	};
}
