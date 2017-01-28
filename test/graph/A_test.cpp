/*
 * A_test.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock_A.h"
#include "mock_A2.h"
#include "A.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_; // for arbitrary mock function arguments
using ::testing::Ge;

// Problem: how to test how many times a public method calls some other class methods?
// - declare submethods as virtual and derive the mock class from the real class (not good, because you open your class for changes
// - copy implementation and use it as an action (invoke) (not good, because test code are not guarantied to stay identical)

// Insight: submethod calls should anyway not be tested, because this is an implementation detail. Testing should focus on correct results.
// In TDD, it is anyway asked to first do a quick implementation that fullfills the requirement and than refactor the code to a better design.
// test code should not be depentend on the realization, otherwise any change/improvement would break your test code ...
// Tests should address classes contracts (requirements)
//
// -> problem is obsolete

// used for mock_A.h based on virtual declared function to define the mock macros
TEST(GraphTest, TestA_checkNumberOfSubMethodCalls)
{
	int ret = 100;
	graph::Mock_A mockA;

	EXPECT_CALL(mockA, subTestFunc(Ge(0)))
	.Times(2)
	.WillOnce(Return(10))
	.WillOnce(Return(10))
	;

	ret = mockA.testFunction(10);

    EXPECT_EQ(20, ret);
}

TEST(GraphTest, TestA2_checkNumberOfSubMethodCalls)
{
	int ret = 100;
	test_graph::Mock_A2 mockA;
	graph::A realA;

	ON_CALL(mockA, testFunction(_))
	// does not work because the invoke simply calls the function in the real class (not tracked) and return real value
	//.WillByDefault(testing::Invoke(&realA, &graph::A::testFunction));
	// works but needs to have a COPY of the real implementation
	.WillByDefault(testing::Invoke(&mockA, &test_graph::Mock_A2::mockImpl_testFunction));

	EXPECT_CALL(mockA, testFunction(10))
	.Times(1)
	;

	EXPECT_CALL(mockA, subTestFunc(Ge(0)))
	.Times(2)
	.WillOnce(Return(10))
	.WillOnce(Return(10))
	;

	ret = mockA.testFunction(10);

    EXPECT_EQ(20, ret);
}

