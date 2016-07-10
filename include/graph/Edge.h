/*
 * Edge.h
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#ifndef EDGE_H_
#define EDGE_H_

//#include "Vertex.h"
#include <tuple>

namespace graph {

class Vertex; //forward declaration

class Edge {
public:
	Edge(Vertex* origin, Vertex* goal, unsigned int edgeId);
	virtual ~Edge();

	unsigned int GetId(void) {return this->id;}
	Vertex* GetStartVertexPtr(void) {return this->link.first;}
	Vertex* GetEndVertexPtr(void) {return this->link.second;}

private:
	unsigned int id;
	std::pair<Vertex*, Vertex*> link;

};

} /* namespace graph */

#endif /* EDGE_H_ */
