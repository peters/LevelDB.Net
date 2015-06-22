#include "LevelDB.LevelDBException.h"
#include <msclr/marshal_cppstd.h>

using namespace LevelDB;
using namespace System;
using namespace msclr::interop;

LevelDBException::LevelDBException(leveldb::Status &status)
	:DbException(marshal_context().marshal_as<String^>(status.ToString()))
{
}
