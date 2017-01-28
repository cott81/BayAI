/*
 * IA.h
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#ifndef SRC_GRAPH_IA_H_
#define SRC_GRAPH_IA_H_

namespace graph {

class IA {
public:

	IA(){};
	virtual ~IA(){};
	//virtual int primFunctionToTest() = 0;
	virtual int testFunction(int a) = 0;

protected:
	virtual int subTestFunc(int num){return 0;};


};

} /* namespace graph */



#endif /* SRC_GRAPH_IA_H_ */
