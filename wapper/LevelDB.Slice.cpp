#include "LevelDB.Slice.h"
#include <Windows.h>

using namespace LevelDB;
using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;

Slice::Slice(const leveldb::Slice& data)
{
	this->buffer = gcnew array<byte>((int)data.size());
	pin_ptr<byte> ptr_r = &buffer[0];
	memcpy_s(ptr_r, buffer->Length, data.data(), buffer->Length);
}

Slice::Slice(const std::string& data)
{
	this->buffer = gcnew array<byte>((int)data.length());
	pin_ptr<byte> ptr_r = &buffer[0];
	memcpy_s(ptr_r, buffer->Length, data.c_str(), buffer->Length);
}

int Slice::CompareTo(Slice other)
{
	for (int i = 0; i < buffer->Length && i < other.buffer->Length; i++)
	{
		int r = buffer[i].CompareTo(other.buffer[i]);
		if (r != 0) return r;
	}
	return buffer->Length.CompareTo(other.buffer->Length);
}

bool Slice::Equals(Slice other)
{
	return CompareTo(other) == 0;
}

bool Slice::Equals(Object^ other)
{
	if (other == nullptr) return false;
	Slice^ o = dynamic_cast<Slice^>(other);
	if (o == nullptr) return false;
	return Equals(*o);
}

int Slice::GetHashCode()
{
	SHA256Managed sha256;
	return BitConverter::ToInt32(sha256.ComputeHash(buffer), 0);
}

array<byte>^ Slice::ToArray()
{
	return buffer;
}

String^ Slice::ToString()
{
	return Encoding::UTF8->GetString(buffer);
}

Slice::operator Slice(array<byte>^ data)
{
	Slice s;
	s.buffer = data;
	return s;
}

Slice::operator Slice(String^ data)
{
	Slice s;
	s.buffer = Encoding::UTF8->GetBytes(data);
	return s;
}

bool Slice::operator < (Slice x, Slice y)
{
	return x.CompareTo(y) < 0;
}

bool Slice::operator <= (Slice x, Slice y)
{
	return x.CompareTo(y) <= 0;
}

bool Slice::operator > (Slice x, Slice y)
{
	return x.CompareTo(y) > 0;
}

bool Slice::operator >= (Slice x, Slice y)
{
	return x.CompareTo(y) >= 0;
}

bool Slice::operator == (Slice x, Slice y)
{
	return x.CompareTo(y) == 0;
}

bool Slice::operator != (Slice x, Slice y)
{
	return x.CompareTo(y) != 0;
}
