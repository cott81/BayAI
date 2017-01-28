/*
 * mock_A.h
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#ifndef TEST_GRAPH_MOCK_A_H_
#define TEST_GRAPH_MOCK_A_H_

#include "gmock/gmock.h"

#include "A.h"

namespace graph {


class Mock_A: public A {
public:

	Mock_A(){};
	virtual ~Mock_A() {};

	MOCK_METHOD1(subTestFunc, int(int num));
};

}



#endif /* TEST_GRAPH_MOCK_A_H_ */
