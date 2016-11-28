// tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
 
/*
TEST(GraphTest, TestTestFunc)
{
	EXPECT_EQ(1,1);
	ASSERT_EQ(1,1);
}
*/




 
int main(int argc, char **argv) {
    //testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    std::cout << "start test"<<std::endl;
    return RUN_ALL_TESTS();
}
