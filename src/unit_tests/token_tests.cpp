#include <gtest/gtest.h>

TEST(sanity, sanity)
{
	EXPECT_EQ(1, 1);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	auto a = RUN_ALL_TESTS();
	__debugbreak();
	return a;
}