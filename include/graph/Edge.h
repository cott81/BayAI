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
	//Edge(Vertex* origin, Vertex* goal);
	virtual ~Edge();

	inline unsigned int GetId(void) {return this->id;}	
	inline Vertex* GetStartVertexPtr(void) {return this->link.first;}
	inline Vertex* GetEndVertexPtr(void) {return this->link.second;}
	void DecreaseStartVertexPtr();
	void DecreaseEndVertexPtr();

	// move to private (need friend for this)
	void SetEdgeId(unsigned int edgeId) {this->id = edgeId;}

private:
	unsigned int id;
	std::pair<Vertex*, Vertex*> link;

};

} /* namespace graph */

#endif /* EDGE_H_ */
