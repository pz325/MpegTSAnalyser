#include "gtest/gtest.h"
#include "Source.hpp"

namespace
{
	const uint32_t DATA_SIZE(10);
}
class TestSource : public testing::Test
{
public:
	TestSource();
	virtual ~TestSource();
	virtual void SetUp();
	virtual void TearDown();
protected:
	LibMpegTS::Source source_;
	uint8_t* pData_;
};

TestSource::TestSource()
{
	pData_ = new uint8_t[DATA_SIZE];
}

TestSource::~TestSource()
{
	delete[] pData_;
	pData_ = nullptr;
}

void TestSource::SetUp() {}
void TestSource::TearDown() {}


TEST_F(TestSource, test_writeTo_from_empty_Source)
{
	// act
	const uint32_t sizeWritten = source_.writeTo(pData_, DATA_SIZE);
	// assert
	EXPECT_EQ(0, sizeWritten);
}

TEST_F(TestSource, test_writeTo_from_Source_having_data_more_than_DATA_SIZE_once)
{
	// arrange
	const std::string data = "abcdefghijklmnopqrstuvwxyz"; // length = 26
	source_.load<LibMpegTS::Source::Source::STRING>(data);
	// act
	const uint32_t sizeWritten = source_.writeTo(pData_, DATA_SIZE);

	// assert
	EXPECT_EQ(DATA_SIZE, sizeWritten);
	EXPECT_EQ(97/*a*/, pData_[0]);
}

TEST_F(TestSource, test_writeTo_from_Source_having_less_data_than_DATA_SIZE_once)
{
	// arrange
	const std::string data = "abcde"; // length = 5
	source_.load<LibMpegTS::Source::Source::STRING>(data);
	
	// act
	const uint32_t sizeWritten = source_.writeTo(pData_, DATA_SIZE);

	// assert
	EXPECT_EQ(data.size(), sizeWritten);
	EXPECT_EQ(97/*a*/, pData_[0]);
}

TEST_F(TestSource, test_writeTo_from_Source_having_data_more_than_double_DATA_SIZE_until_readout)
{
	// arrange
	const std::string data = "abcdefghijklmnopqrstuvwxyz"; // length = 26
	source_.load<LibMpegTS::Source::Source::STRING>(data);

	// act
	uint32_t sizeWritten = source_.writeTo(pData_, DATA_SIZE);
	EXPECT_EQ(DATA_SIZE, sizeWritten);
	EXPECT_EQ(97/*a*/, pData_[0]);
	sizeWritten = source_.writeTo(pData_, DATA_SIZE);
	EXPECT_EQ(DATA_SIZE, sizeWritten);
	EXPECT_EQ(107/*a*/, pData_[0]);
	sizeWritten = source_.writeTo(pData_, DATA_SIZE);
	EXPECT_EQ(data.size() - 2 * DATA_SIZE, sizeWritten);
	EXPECT_EQ(117/*a*/, pData_[0]);
}

TEST_F(TestSource, test_reset_read_once)
{
	// arrange
	const std::string data = "abcdefghijklmnopqrstuvwxyz"; // length = 26
	source_.load<LibMpegTS::Source::Source::STRING>(data);

	// act
	source_.writeTo(pData_, DATA_SIZE);
	source_.reset();
	const uint32_t sizeWritten = source_.writeTo(pData_, DATA_SIZE);

	// assert
	EXPECT_EQ(DATA_SIZE, sizeWritten);
	EXPECT_EQ(97/*a*/, pData_[0]);
}

TEST_F(TestSource, test_reset_read_twice)
{
	// arrange
	const std::string data = "abcdefghijklmnopqrstuvwxyz"; // length = 26
	source_.load<LibMpegTS::Source::Source::STRING>(data);

	// act
	source_.writeTo(pData_, DATA_SIZE);
	source_.writeTo(pData_, DATA_SIZE);
	source_.reset();
	const uint32_t sizeWritten = source_.writeTo(pData_, DATA_SIZE);

	// assert
	EXPECT_EQ(DATA_SIZE, sizeWritten);
	EXPECT_EQ(97/*a*/, pData_[0]);
}

TEST_F(TestSource, test_size)
{
	// arrange
	const std::string data = "abcdefghijklmnopqrstuvwxyz"; // length = 26
	// act
	source_.load<LibMpegTS::Source::Source::STRING>(data);
	// assert
	EXPECT_EQ(data.size(), source_.size());
}

