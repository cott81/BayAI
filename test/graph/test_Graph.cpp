/*
 * test_Graph.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "graph/Graph.h"
#include "mock_A.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_; // for arbitrary mock function arguments
using ::testing::Ge;

TEST(GraphTest, SomethingToTest_test)
{
	graph::Mock_A ma;
	EXPECT_CALL(ma, testFunction(Ge(0)))
	.Times(AtLeast(1))
	.WillOnce(Return(100))
	;

	graph::Graph g (graph::ADJACENCY_LIST);

	int ret = g.SomethingToTest(1.0, &ma);
	//int ret = -1.0;
	std::cout<<"func out: " << ret << std::endl;

    EXPECT_EQ(100, ret);
}

