/*
 * mock_A.h
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#ifndef TEST_GRAPH_MOCK_A_H_
#define TEST_GRAPH_MOCK_A_H_

#include "gmock/gmock.h"

namespace graph {

class Mock_A : public IA {
public:

	Mock_A(){};
	virtual ~Mock_A() {};

	/*
	virtual int testFunction(int a)
	{
		// mocked return
		return a;
	}
	*/

	MOCK_METHOD1(testFunction, int(int a));
};

}



#endif /* TEST_GRAPH_MOCK_A_H_ */
