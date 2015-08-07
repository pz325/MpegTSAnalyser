// MpegTSAnalyser.cpp : Defines the entry point for the console application.
//

#include "Source.hpp"

#include <iostream>

int main()
{
	LibMpegTS::Source source;
	source.load<LibMpegTS::Source::FILE>("resource/00.ts");

	const uint32_t dataSize = 50;
	uint8_t* pData = new uint8_t[dataSize];
	const uint32_t sizeWritten = source.writeTo(pData, dataSize);
	std::cout << pData[0] << " size " << sizeWritten << std::endl;

	return 0;
}

