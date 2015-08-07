#pragma once

#include "leveldb/filter_policy.h"

namespace LevelDB
{
	public ref class FilterPolicy abstract
	{
	internal:
		const leveldb::FilterPolicy* policy;
	internal:
		FilterPolicy();
	};
}
