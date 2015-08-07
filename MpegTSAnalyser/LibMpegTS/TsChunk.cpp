#include "TsChunk.hpp"
#include <string.h>

using namespace LibMpegTS;

TsChunk::TsChunk()
	: data_(nullptr),
	size_(0)
{}

TsChunk::~TsChunk()
{
	clear();
}

void TsChunk::setData(const uint8_t* data, const uint32_t size)
{
	clear();
	data_ = new uint8_t[size];
	memcpy(data_, data, size);
	size_ = size;
}

void TsChunk::clear()
{
	delete[] data_;
	data_ = nullptr;
	size_ = 0;
}
