#include "Source.hpp"

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace LibMpegTS;

// class Source
Source::Source()
: pData_(nullptr),
size_(0),
readIndex_(0)
{}


Source::~Source() {}

uint32_t Source::writeTo(uint8_t* pData, const uint32_t sizeToRead)
{
	const uint32_t sizeRead = std::min(size_ - readIndex_, sizeToRead);
	memcpy(pData, pData_.get() + readIndex_, sizeRead);
	readIndex_ += sizeRead;
	return sizeRead;
}

uint32_t Source::size() const
{
	return size_;
}

void Source::reset()
{
	readIndex_ = 0;
}

template<>
void Source::load<Source::SourceType::FILE>(const std::string& uri)
{
	std::cout << "loading [" << uri << "] from FILE" << std::endl;
		
	::FILE* f = ::fopen(uri.c_str(), "rb");
	::fseek(f, 0, SEEK_END);
	size_ = ::ftell(f);
	::fseek(f, 0, SEEK_SET);

	pData_ = std::unique_ptr<uint8_t[]>(new uint8_t[size_]);
	::fread(pData_.get(), size_, 1, f);
	::fclose(f);
	
	reset();
}

template<>
void Source::load<Source::SourceType::HTTP>(const std::string& uri)
{
	std::cout << "loading [" << uri << "] from HTTP" << std::endl;
	reset();
}

template<>
void Source::load<Source::SourceType::STRING>(const std::string& uri)
{
	pData_ = std::unique_ptr<uint8_t[]>(new uint8_t[uri.size()]);
	memcpy(pData_.get(), uri.c_str(), uri.size());
	size_ = uri.size();
	reset();
}
