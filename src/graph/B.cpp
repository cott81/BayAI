/*
 * A.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#include "B.h"

namespace graph {

B::B() {
	this->member = 75;
}

B::~B() {
}

/*
int B::primFunctionToTest()
{
	int sum = 0;

	sum = sum + testFunction(1);
	sum = sum + testFunction(1);
	sum = sum + testFunction(1);

	return sum;
}
*/

int B::testFunction(int a)
{
	int ret = 0;

	ret = ret + subTestFunc(a);
	ret = ret + subTestFunc(a);

	return ret;
}

int B::subTestFunc(int num)
{
	return num;
}

} /* namespace graph */
