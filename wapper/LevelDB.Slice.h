#pragma once

#include "leveldb/slice.h"
#include <Windows.h>

namespace LevelDB
{
	public value class Slice
		:System::IComparable < Slice >,
		System::IEquatable < Slice >
	{
	internal:
		array<byte>^ buffer;
	internal:
		Slice(const leveldb::Slice& data);
		Slice(const std::string& data);
	public:
		virtual int CompareTo(Slice other);
		virtual bool Equals(Slice other);
		virtual bool Equals(System::Object^ other) override;
		virtual int GetHashCode() override;
		array<byte>^ ToArray();
		bool ToBoolean();
		byte ToByte();
		double ToDouble();
		short ToInt16();
		int ToInt32();
		long long ToInt64();
		float ToSingle();
		virtual System::String^ ToString() override;
		unsigned short ToUInt16();
		unsigned int ToUInt32();
		unsigned long long ToUInt64();
	public:
		static operator Slice(array<byte>^ data);
		static operator Slice(bool data);
		static operator Slice(byte data);
		static operator Slice(double data);
		static operator Slice(short data);
		static operator Slice(int data);
		static operator Slice(long long data);
		static operator Slice(float data);
		static operator Slice(System::String^ data);
		static operator Slice(unsigned short data);
		static operator Slice(unsigned int data);
		static operator Slice(unsigned long long data);
		static bool operator < (Slice x, Slice y);
		static bool operator <= (Slice x, Slice y);
		static bool operator > (Slice x, Slice y);
		static bool operator >= (Slice x, Slice y);
		static bool operator == (Slice x, Slice y);
		static bool operator != (Slice x, Slice y);
	};
}
