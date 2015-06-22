#pragma once

#include "leveldb\status.h"

namespace LevelDB
{
	public ref class LevelDBException :
		public System::Data::Common::DbException
	{
	internal:
		LevelDBException(leveldb::Status &status);
	};
}
