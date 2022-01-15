// tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>


int main(int argc, char **argv) {
    //testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    std::cout << "start test"<<std::endl;
    return RUN_ALL_TESTS();
}
