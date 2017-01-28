/*
 * A.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#include "A.h"

namespace graph {

A::A() {
	// TODO Auto-generated constructor stub

}

A::~A() {
	// TODO Auto-generated destructor stub
}

/*
int A::primFunctionToTest()
{
	int sum = 0;

	sum = sum + testFunction(1);
	sum = sum + testFunction(1);
	sum = sum + testFunction(1);

	return sum;
}
*/

int A::testFunction(int a)
{
	int ret = 0;

	ret = ret + subTestFunc(a);
	ret = ret + subTestFunc(a);

	return ret;
}

int A::subTestFunc(int num)
{
	return num;
}

} /* namespace graph */
