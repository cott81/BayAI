/*
 * Vertex.h
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "Edge.h"
#include <vector>

namespace graph {

class Vertex {
public:
	Vertex(unsigned int id);
	virtual ~Vertex();

	int AddIncomingEdge(Edge* incomingEdgePtr);
	int RemoveIncomingEdge(unsigned int originVertexId);
	int AddOutgoingEdge(Edge* outgoingEdgePtr);
	int RemoveOutgoingEdge(unsigned int endVertexId);

	int PrintInEdges();
	int PrintOutEdges();

	inline unsigned int GetId(void) {return this->id;}
	inline std::vector<graph::Edge*> GetOutEdges(void) {return this->out_edges;}
	inline std::vector<graph::Edge*> GetInEdges(void) {return this->in_edges;}

private:
	std::vector<graph::Edge*> out_edges;		// outgoing edges store the edge objects
	std::vector<graph::Edge*> in_edges;			// incoming edges store pointers
	unsigned int id;


};

} /* namespace graph */

#endif /* VERTEX_H_ */
