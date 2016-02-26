/*
 * Node.h
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#ifndef NODE_H_
#define NODE_H_

namespace bayes_net {

class Node: public graph::Vertex {
public:
	Node();
	virtual ~Node();
};

} /* namespace bayes_net */

#endif /* NODE_H_ */
