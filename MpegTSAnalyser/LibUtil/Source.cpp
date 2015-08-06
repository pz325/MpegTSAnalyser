#include "Source.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace LibUtil;

// class Source
Source::Source()
: data_(nullptr),
size_(0)
{}


Source::~Source()
{
	delete[] data_;
	data_ = nullptr;
}

uint8_t* Source::data() const
{
	return data_;
}

uint32_t Source::size() const
{
	return size_;
}

template<>
void Source::load<Source::SourceType::FILE>(const std::string& uri)
{
	std::cout << "loading [" << uri << "] from FILE" << std::endl;

	::FILE* f = ::fopen(uri.c_str(), "rb");
	::fseek(f, 0, SEEK_END);
	size_ = ::ftell(f);
	::fseek(f, 0, SEEK_SET);

	data_ = new uint8_t[size_];
	::fread(data_, size_, 1, f);
	::fclose(f);
}

template<>
void Source::load<Source::SourceType::HTTP>(const std::string& uri)
{
	std::cout << "loading [" << uri << "] from HTTP" << std::endl;
}