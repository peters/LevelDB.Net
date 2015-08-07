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
	this->!DB();
}

DB::!DB(void)
{
	if (db_inner != nullptr)
	{
		delete db_inner;
		db_inner = nullptr;
	}
}

void DB::Delete(WriteOptions^ options, Slice key)
{
	pin_ptr<byte> ptr_k = &key.buffer[0];
	leveldb::Slice k((char*)ptr_k, key.buffer->Length);
	leveldb::Status status = db_inner->Delete(options->ToUnmanaged(), k);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

Slice DB::Get(ReadOptions^ options, Slice key)
{
	std::string value;
	pin_ptr<byte> ptr_k = &key.buffer[0];
	leveldb::Slice k((char*)ptr_k, key.buffer->Length);
	leveldb::Status status = db_inner->Get(options->ToUnmanaged(), k, &value);
	if (!status.ok())
		throw gcnew LevelDBException(status);
	return Slice(value);
}

Snapshot^ DB::GetSnapshot()
{
	return gcnew Snapshot(db_inner);
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

void DB::Put(WriteOptions^ options, Slice key, Slice value)
{
	pin_ptr<byte> ptr_k = &key.buffer[0];
	pin_ptr<byte> ptr_v = &value.buffer[0];
	leveldb::Slice k((char*)ptr_k, key.buffer->Length);
	leveldb::Slice v((char*)ptr_v, value.buffer->Length);
	leveldb::Status status = db_inner->Put(options->ToUnmanaged(), k, v);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}

bool DB::TryGet(ReadOptions^ options, Slice key, Slice% value)
{
	std::string value_i;
	pin_ptr<byte> ptr_k = &key.buffer[0];
	leveldb::Slice k((char*)ptr_k, key.buffer->Length);
	leveldb::Status status = db_inner->Get(options->ToUnmanaged(), k, &value_i);
	if (!status.ok())
		return false;
	value = Slice(value_i);
	return true;
}

void DB::Write(WriteOptions^ options, WriteBatch^ updates)
{
	leveldb::Status status = db_inner->Write(options->ToUnmanaged(), updates->write_batch);
	if (!status.ok())
		throw gcnew LevelDBException(status);
}
