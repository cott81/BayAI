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

	virtual int testFunction(int a);
};

} /* namespace graph */

#endif /* SRC_GRAPH_A_H_ */
