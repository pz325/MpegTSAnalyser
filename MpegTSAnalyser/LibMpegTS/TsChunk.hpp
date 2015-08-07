#pragma once

#include <cstdint>

namespace LibMpegTS
{
	class TsChunk
	{
	public:
		TsChunk();
		~TsChunk();
		void setData(const uint8_t* data, const uint32_t size);

	private:
		uint8_t* data_;
		uint32_t size_;

		void clear();
	};
} // namespace LibMpegTS
