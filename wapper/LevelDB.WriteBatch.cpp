#include "LevelDB.WriteBatch.h"
#include <msclr/marshal.h>

using namespace LevelDB;
using namespace System;
using namespace msclr::interop;

WriteBatch::WriteBatch(void)
{
	this->write_batch = new leveldb::WriteBatch();
}

WriteBatch::!WriteBatch(void)
{
	if (write_batch != NULL)
	{
		delete write_batch;
		write_batch = NULL;
	}
}

void WriteBatch::Clear()
{
	write_batch->Clear();
}

void WriteBatch::Delete(array<byte>^ key)
{
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	write_batch->Delete(k);
}

void WriteBatch::Delete(String^ key)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	write_batch->Delete(k);
}

void WriteBatch::Put(array<byte>^ key, array<byte>^ value)
{
	pin_ptr<byte> ptr_k = &key[0];
	pin_ptr<byte> ptr_v = &value[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Slice v((char*)ptr_v, value->Length);
	write_batch->Put(k, v);
}

void WriteBatch::Put(array<byte>^ key, String^ value)
{
	marshal_context context;
	pin_ptr<byte> ptr_k = &key[0];
	leveldb::Slice k((char*)ptr_k, key->Length);
	leveldb::Slice v(context.marshal_as<const char*>(value));
	write_batch->Put(k, v);
}

void WriteBatch::Put(String^ key, array<byte>^ value)
{
	marshal_context context;
	pin_ptr<byte> ptr_v = &value[0];
	leveldb::Slice k(context.marshal_as<const char*>(key));
	leveldb::Slice v((char*)ptr_v, value->Length);
	write_batch->Put(k, v);
}

void WriteBatch::Put(String^ key, String^ value)
{
	marshal_context context;
	leveldb::Slice k(context.marshal_as<const char*>(key));
	leveldb::Slice v(context.marshal_as<const char*>(value));
	write_batch->Put(k, v);
}
