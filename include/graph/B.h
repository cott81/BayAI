/*
 * A.h
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#ifndef SRC_GRAPH_B_H_
#define SRC_GRAPH_B_H_

namespace graph {

class B
{
public:
	B();
	virtual ~B();

	//virtual int primFunctionToTest();
	virtual int testFunction(int a);

protected:
	virtual int subTestFunc(int num);

	int member;

};

} /* namespace graph */

#endif /* SRC_GRAPH_B_H_ */
