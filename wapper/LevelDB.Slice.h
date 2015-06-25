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
		virtual System::String^ ToString() override;
	public:
		static operator Slice(array<byte>^ data);
		static operator Slice(System::String^ data);
		static bool operator < (Slice x, Slice y);
		static bool operator <= (Slice x, Slice y);
		static bool operator > (Slice x, Slice y);
		static bool operator >= (Slice x, Slice y);
		static bool operator == (Slice x, Slice y);
		static bool operator != (Slice x, Slice y);
	};
}
