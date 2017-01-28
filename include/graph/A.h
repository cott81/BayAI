/*
 * A.h
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#ifndef SRC_GRAPH_A_H_
#define SRC_GRAPH_A_H_

#include "IA.h"

namespace graph {

class A : public IA {
public:
	A();
	virtual ~A();

	//virtual int primFunctionToTest();
	virtual int testFunction(int a);

protected:
	virtual int subTestFunc(int num);

};

} /* namespace graph */

#endif /* SRC_GRAPH_A_H_ */
