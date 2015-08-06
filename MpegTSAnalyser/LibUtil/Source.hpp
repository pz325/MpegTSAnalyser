#pragma once

#include <string>

namespace LibUtil
{
	class Source
	{
	public:
		enum SourceType
		{
			FILE,
			HTTP
		};

		Source();
		~Source();
		
		template<SourceType type>
		void load(const std::string& uri);

		uint8_t* data() const;
		uint32_t size() const;

	private:
		uint8_t* data_;
		uint32_t size_;
	};
} // namespace LibUtil