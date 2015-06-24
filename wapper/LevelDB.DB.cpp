#include "LevelDB.DB.h"
#include "LevelDB.LevelDBException.h"
#include <msclr/marshal.h>
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
	DeleteInternal(k);
}

void DB::Delete(String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	DeleteInternal(k);
}

array<byte>^ DB::Get(array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	std::string value = GetInternal(k);
	array<byte>^ result = gcnew array<byte>((int)value.length());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, value.c_str(), result->Length);
	return result;
}

array<byte>^ DB::Get(String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	std::string value = GetInternal(k);
	array<byte>^ result = gcnew array<byte>((int)value.length());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, value.c_str(), result->Length);
	return result;
}

String^ DB::GetString(array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	std::string value = GetInternal(k);
	return marshal_as<String^>(value);
}

String^ DB::GetString(String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	std::string value = GetInternal(k);
	return marshal_as<String^>(value);
}

DB^ DB::Open(String^ name)
{
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::DB* db_inner;
	leveldb::Status status = leveldb::DB::Open(options, marshal_as<std::string>(name), &db_inner);
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
	PutInternal(k, v);
}

void DB::Put(array<byte>^ key, String^ value)
{
	marshal_context context;
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Slice v(context.marshal_as<const char*>(value));
	PutInternal(k, v);
}

void DB::Put(String^ key, array<byte>^ value)
{
	marshal_context context;
	pin_ptr<byte> ptr_v = &value[0];
	leveldb::Slice k(context.marshal_as<const char*>(key));
	leveldb::Slice v((char*)ptr_v, value->Length);
	PutInternal(k, v);
}

void DB::Put(String^ key, String^ value)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	leveldb::Slice v(context.marshal_as<const char*>(value));
	PutInternal(k, v);
}

void DB::Write(WriteBatch^ updates)
{
	leveldb::Status status = db_inner->Write(leveldb::WriteOptions(), updates->write_batch);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

void DB::DeleteInternal(leveldb::Slice& key)
{
	leveldb::Status status = db_inner->Delete(leveldb::WriteOptions(), key);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

std::string DB::GetInternal(leveldb::Slice& key)
{
	std::string value;
	leveldb::Status status = db_inner->Get(leveldb::ReadOptions(), key, &value);
	if (!status.ok())
		throw gcnew LevelDBException(status);
	return value;
}

void DB::PutInternal(leveldb::Slice& key, leveldb::Slice& value)
{
	leveldb::Status status = db_inner->Put(leveldb::WriteOptions(), key, value);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}
