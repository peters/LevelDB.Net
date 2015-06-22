#include "LevelDB.DB.h"
#include "LevelDB.LevelDBException.h"
#include <msclr/marshal_cppstd.h>

using namespace LevelDB;
using namespace System;
using namespace msclr::interop;

DB::DB(leveldb::DB* db_inner)
	:db_inner(db_inner)
{
}

DB::~DB(void)
{
	if (db_inner != NULL)
	{
		delete db_inner;
		db_inner = NULL;
	}
}

void DB::Delete(array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Status status = db_inner->Delete(leveldb::WriteOptions(), k);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

array<byte>^ DB::Get(array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	std::string value;
	leveldb::Status status = db_inner->Get(leveldb::ReadOptions(), k, &value);
	if (!status.ok())
		throw gcnew LevelDBException(status);
	array<byte>^ result = gcnew array<byte>((int)value.length());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, value.c_str(), result->Length);
	return result;
}

DB^ DB::Open(String^ name)
{
	marshal_context context;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::DB* db_inner;
	leveldb::Status status = leveldb::DB::Open(options, context.marshal_as<std::string>(name), &db_inner);
	if (!status.ok())
		throw gcnew LevelDBException(status);
	return gcnew DB(db_inner);
}

void DB::Put(array<byte>^ key, array<byte>^ value)
{
	pin_ptr<byte> ptr_k = &key[0];
	pin_ptr<byte> ptr_v = &value[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Slice v((char*)ptr_v, value->Length);
	leveldb::Status status = db_inner->Put(leveldb::WriteOptions(), k, v);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}
