#include "LevelDB.Iterator.h"
#include "LevelDB.LevelDBException.h"
#include <msclr/marshal.h>

using namespace LevelDB;
using namespace System;
using namespace msclr::interop;

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

array<byte>^ Iterator::Key()
{
	leveldb::Slice key = iter->key();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
	array<byte>^ result = gcnew array<byte>((int)key.size());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, key.data(), result->Length);
	return result;
}

String^ Iterator::KeyAsString()
{
	leveldb::Slice key = iter->key();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
	return marshal_as<String^>(key.data());
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

void Iterator::Seek(array<byte>^ target)
{
	pin_ptr<byte> ptr_t = &target[0];
	leveldb::Slice t((char*)ptr_t, target->Length);
	iter->Seek(t);
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
}

void Iterator::Seek(String^ target)
{
	marshal_context context;
	leveldb::Slice t(context.marshal_as<const char*>(target));
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

array<byte>^ Iterator::Value()
{
	leveldb::Slice value = iter->value();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
	array<byte>^ result = gcnew array<byte>((int)value.size());
	pin_ptr<byte> ptr_r = &result[0];
	memcpy_s(ptr_r, result->Length, value.data(), result->Length);
	return result;
}

String^ Iterator::ValueAsString()
{
	leveldb::Slice value = iter->value();
	if (!iter->status().ok())
		throw gcnew LevelDBException(iter->status());
	return marshal_as<String^>(value.data());
}
