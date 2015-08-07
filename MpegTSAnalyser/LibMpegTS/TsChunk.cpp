#include "TsChunk.hpp"
#include <string.h>

using namespace LibMpegTS;

TsChunk::TsChunk()
	: pData_(nullptr),
	size_(0)
{}

TsChunk::~TsChunk() {}

void TsChunk::setData(const uint8_t* data, const uint32_t size)
{
	pData_ = std::unique_ptr<uint8_t[]>(new uint8_t[size]);
	memcpy(pData_.get(), data, size);
	size_ = size;
}
