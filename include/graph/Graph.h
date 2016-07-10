/*
 * Graph.h
 *
 *  Created on: Jul 8, 2016
 *      Author: dominik
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

#include "Vertex.h"

#include <vector>

namespace graph {


class Graph {
public:
	Graph();
	virtual ~Graph();

	unsigned int GenerateVertexId();
	int AddVertex();
	//int RemoveVertex();

	unsigned int GenerateEdgeId();
	int AddEdge(int startVertexId, int endVertexId);
	//int RemoveEdge();

	Vertex* GetVertex(unsigned int vertexId);

	void PrintVertices();
	void PrintEdges();

private:
	unsigned int vertexCounter;
	unsigned int edgeCounter;
	const unsigned int EDGE_COUNTER_OFFSET = 1000;

	//adjacency list
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;

};

} /* namespace graph */

#endif /* SRC_GRAPH_GRAPH_H_ */
