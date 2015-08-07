#include "LevelDB.Options.h"

using namespace LevelDB;

Options::Options(void)
{
	this->Compression = CompressionType::SnappyCompression;
}

leveldb::Options Options::ToUnmanaged()
{
	leveldb::Options options;
	options.create_if_missing = CreateIfMissing;
	options.error_if_exists = ErrorIfExists;
	options.paranoid_checks = ParanoidChecks;
	options.write_buffer_size = WriteBufferSize;
	options.max_open_files = MaxOpenFiles;
	options.block_size = BlockSize;
	options.block_restart_interval = BlockRestartInterval;
	options.compression = (leveldb::CompressionType)(int)Compression;
	options.filter_policy = FilterPolicy == nullptr ? nullptr : FilterPolicy->policy;
	return options;
}
