#include "LevelDB.WriteBatch.h"

using namespace LevelDB;
using namespace System;

WriteBatch::WriteBatch(void)
{
	this->write_batch = new leveldb::WriteBatch();
}

WriteBatch::!WriteBatch(void)
{
	if (write_batch != nullptr)
	{
		delete write_batch;
		write_batch = nullptr;
	}
}

void WriteBatch::Clear()
{
	write_batch->Clear();
}

void WriteBatch::Delete(Slice key)
{
	pin_ptr<byte> ptr_k = &key.buffer[0];
	leveldb::Slice k((char*)ptr_k, key.buffer->Length);
	write_batch->Delete(k);
}

void WriteBatch::Put(Slice key, Slice value)
{
	pin_ptr<byte> ptr_k = &key.buffer[0];
	pin_ptr<byte> ptr_v = &value.buffer[0];
	leveldb::Slice k((char*)ptr_k, key.buffer->Length);
	leveldb::Slice v((char*)ptr_v, value.buffer->Length);
	write_batch->Put(k, v);
}
