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

bool Slice::ToBoolean()
{
	if (buffer->Length != sizeof(bool))
		throw gcnew InvalidCastException();
	return BitConverter::ToBoolean(buffer, 0);
}

byte Slice::ToByte()
{
	if (buffer->Length != sizeof(byte))
		throw gcnew InvalidCastException();
	return buffer[0];
}

double Slice::ToDouble()
{
	if (buffer->Length != sizeof(double))
		throw gcnew InvalidCastException();
	return BitConverter::ToDouble(buffer, 0);
}

short Slice::ToInt16()
{
	if (buffer->Length != sizeof(short))
		throw gcnew InvalidCastException();
	return BitConverter::ToInt16(buffer, 0);
}

int Slice::ToInt32()
{
	if (buffer->Length != sizeof(int))
		throw gcnew InvalidCastException();
	return BitConverter::ToInt32(buffer, 0);
}

long long Slice::ToInt64()
{
	if (buffer->Length != sizeof(long long))
		throw gcnew InvalidCastException();
	return BitConverter::ToInt64(buffer, 0);
}

float Slice::ToSingle()
{
	if (buffer->Length != sizeof(float))
		throw gcnew InvalidCastException();
	return BitConverter::ToSingle(buffer, 0);
}

String^ Slice::ToString()
{
	return Encoding::UTF8->GetString(buffer);
}

unsigned short Slice::ToUInt16()
{
	if (buffer->Length != sizeof(unsigned short))
		throw gcnew InvalidCastException();
	return BitConverter::ToUInt16(buffer, 0);
}

unsigned int Slice::ToUInt32()
{
	if (buffer->Length != sizeof(unsigned int))
		throw gcnew InvalidCastException();
	return BitConverter::ToUInt32(buffer, 0);
}

unsigned long long Slice::ToUInt64()
{
	if (buffer->Length != sizeof(unsigned long long))
		throw gcnew InvalidCastException();
	return BitConverter::ToUInt64(buffer, 0);
}

Slice::operator Slice(array<byte>^ data)
{
	Slice s;
	s.buffer = data;
	return s;
}

Slice::operator Slice(bool data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(byte data)
{
	Slice s;
	s.buffer = gcnew array < byte > { data };
	return s;
}

Slice::operator Slice(double data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(short data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(int data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(long long data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(float data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(String^ data)
{
	Slice s;
	s.buffer = Encoding::UTF8->GetBytes(data);
	return s;
}

Slice::operator Slice(unsigned short data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(unsigned int data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
	return s;
}

Slice::operator Slice(unsigned long long data)
{
	Slice s;
	s.buffer = BitConverter::GetBytes(data);
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
