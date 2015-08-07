#include "TsChunk.hpp"
#include <string.h>

using namespace LibMpegTS;

TsChunk::TsChunk()
	: pData_(nullptr),
	size_(0)
{}

TsChunk::~TsChunk()
{
	clear();
}

void TsChunk::setData(const uint8_t* data, const uint32_t size)
{
	clear();
	pData_ = new uint8_t[size];
	memcpy(pData_, data, size);
	size_ = size;
}

void TsChunk::clear()
{
	delete[] pData_;
	pData_ = nullptr;
	size_ = 0;
}
