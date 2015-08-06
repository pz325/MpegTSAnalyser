// MpegTSAnalyser.cpp : Defines the entry point for the console application.
//

#include "Source.hpp"

#include <iostream>

int main()
{
	LibUtil::Source source;
	source.load<LibUtil::Source::FILE>("resource/00.ts");
	uint8_t* data = source.data();
	const uint32_t size = source.size();
	std::cout << data[0] << " size " << size << std::endl;

	return 0;
}

