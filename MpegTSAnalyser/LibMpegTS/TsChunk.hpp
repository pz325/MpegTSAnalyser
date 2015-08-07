#pragma once

#include <cstdint>

namespace LibMpegTS
{
	class TsChunk
	{
	public:
		static const uint32_t SIZE = 512 * 1024;

		TsChunk();
		~TsChunk();
		void setData(const uint8_t* pData, const uint32_t size = SIZE);

	private:
		uint8_t* pData_;
		uint32_t size_;

		void clear();
	};
} // namespace LibMpegTS
