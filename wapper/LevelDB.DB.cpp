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

void DB::Delete(WriteOptions^ options, array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	DeleteInternal(options, k);
}

void DB::Delete(WriteOptions^ options, String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	DeleteInternal(options, k);
}

array<byte>^ DB::Get(ReadOptions^ options, array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	std::string value = GetInternal(options, k);
	array<byte>^ result = gcnew array<byte>((int)value.length());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, value.c_str(), result->Length);
	return result;
}

array<byte>^ DB::Get(ReadOptions^ options, String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	std::string value = GetInternal(options, k);
	array<byte>^ result = gcnew array<byte>((int)value.length());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, value.c_str(), result->Length);
	return result;
}

Snapshot^ DB::GetSnapshot()
{
	return gcnew Snapshot(db_inner);
}

String^ DB::GetString(ReadOptions^ options, array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	std::string value = GetInternal(options, k);
	return marshal_as<String^>(value);
}

String^ DB::GetString(ReadOptions^ options, String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	std::string value = GetInternal(options, k);
	return marshal_as<String^>(value);
}

Iterator^ DB::NewIterator(ReadOptions^ options)
{
	return gcnew Iterator(db_inner->NewIterator(options->ToUnmanaged()));
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

void DB::Put(WriteOptions^ options, array<byte>^ key, array<byte>^ value)
{
	pin_ptr<byte> ptr_k = &key[0];
	pin_ptr<byte> ptr_v = &value[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Slice v((char*)ptr_v, value->Length);
	PutInternal(options, k, v);
}

void DB::Put(WriteOptions^ options, array<byte>^ key, String^ value)
{
	marshal_context context;
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Slice v(context.marshal_as<const char*>(value));
	PutInternal(options, k, v);
}

void DB::Put(WriteOptions^ options, String^ key, array<byte>^ value)
{
	marshal_context context;
	pin_ptr<byte> ptr_v = &value[0];
	leveldb::Slice k(context.marshal_as<const char*>(key));
	leveldb::Slice v((char*)ptr_v, value->Length);
	PutInternal(options, k, v);
}

void DB::Put(WriteOptions^ options, String^ key, String^ value)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	leveldb::Slice v(context.marshal_as<const char*>(value));
	PutInternal(options, k, v);
}

void DB::Write(WriteOptions^ options, WriteBatch^ updates)
{
	leveldb::Status status = db_inner->Write(options->ToUnmanaged(), updates->write_batch);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

void DB::DeleteInternal(WriteOptions^ options, leveldb::Slice& key)
{
	leveldb::Status status = db_inner->Delete(options->ToUnmanaged(), key);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

std::string DB::GetInternal(ReadOptions^ options, leveldb::Slice& key)
{
	std::string value;
	leveldb::Status status = db_inner->Get(options->ToUnmanaged(), key, &value);
	if (!status.ok())
		throw gcnew LevelDBException(status);
	return value;
}

void DB::PutInternal(WriteOptions^ options, leveldb::Slice& key, leveldb::Slice& value)
{
	leveldb::Status status = db_inner->Put(options->ToUnmanaged(), key, value);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}
