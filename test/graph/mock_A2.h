/*
 * mock_A.h
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#ifndef TEST_GRAPH_MOCK_A2_H_
#define TEST_GRAPH_MOCK_A2_H_

#include "gmock/gmock.h"

#include "IA.h"
#include "A.h"

namespace test_graph {


class Mock_A2 : public graph::IA {
public:


	Mock_A2()
	{
	};

	virtual ~Mock_A2() {};

	/*
	int testFunction(int num)
	{
		// call the
		int a = a.testFunction(num);
		return 0;
	};
	*/
	MOCK_METHOD1(testFunction, int(int a));

	MOCK_METHOD1(subTestFunc, int(int num));

	// this is duplicated code for the real function to check subfunction calls
	int mockImpl_testFunction(int a)
	{
		int ret = 0;

		ret = ret + subTestFunc(a);
		ret = ret + subTestFunc(a);

		return ret;
	}

};

}



#endif /* TEST_GRAPH_MOCK_A2_H_ */
