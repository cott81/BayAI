/*
 * WeightedGraph.h
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#ifndef WEIGHTEDGRAPH_H_
#define WEIGHTEDGRAPH_H_

#include "Graph.h"
#include "B.h"
#include "Edge.h"
#include "WeightedEdge.h"

namespace a_star {

class WeightedGraph 
	: public graph::Graph
{
public:
	WeightedGraph();
	virtual ~WeightedGraph();

	void PrintEdges();

	using graph::Graph::AddEdge;
	int AddEdge(unsigned int startVertexId, unsigned int endVertexId, double edgeWeight);

	std::string GenerateDOTDescription();

protected:

	graph::Edge* GenerateEdgeFrom(unsigned int startVertexId, unsigned int endVertexId, unsigned int edgeId);

	double tempEdgeWeight = 1.0;
};

} /* namespace a_star */

#endif /* WEIGHTEDGRAPH_H_ */
