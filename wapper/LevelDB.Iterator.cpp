#include "LevelDB.Iterator.h"
#include "LevelDB.LevelDBException.h"

using namespace LevelDB;
using namespace System;

Iterator::Iterator(leveldb::Iterator* iter)
	:iter(iter)
{
}

Iterator::~Iterator(void)
{
	this->!Iterator();
}

Iterator::!Iterator(void)
{
	if (iter != NULL)
	{
		delete iter;
		iter = NULL;
	}
}

Slice Iterator::Key()
{
	leveldb::Slice key = iter->key();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
	return Slice(key);
}

void Iterator::Next()
{
	iter->Next();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
}

void Iterator::Prev()
{
	iter->Prev();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
}

void Iterator::Seek(Slice target)
{
	pin_ptr<byte> ptr_t = &target.buffer[0];
	leveldb::Slice t((char*)ptr_t, target.buffer->Length);
	iter->Seek(t);
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
}

void Iterator::SeekToFirst()
{
	iter->SeekToFirst();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
}

void Iterator::SeekToLast()
{
	iter->SeekToLast();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
}

bool Iterator::Valid()
{
	return iter->Valid();
}

Slice Iterator::Value()
{
	leveldb::Slice value = iter->value();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
	return Slice(value);
}
