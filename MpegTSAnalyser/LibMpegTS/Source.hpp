#pragma once

#include <string>
#include <memory>

namespace LibMpegTS
{
	class Source
	{
	public:
		enum SourceType
		{
			FILE,
			HTTP,
			STRING // this type can be used for testing: reading std::string
		};

		Source();
		~Source();
		uint32_t writeTo(uint8_t* pData, const uint32_t sizeToRead);
		uint32_t size() const;
		void reset();

		template<SourceType type>
		void load(const std::string& uri);

	private:
		std::unique_ptr<uint8_t[]> pData_;
		uint32_t size_;
		uint32_t readIndex_;
	};
} // namespace LibUtil