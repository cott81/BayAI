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
#include <string>

#include "IA.h"

namespace graph {

enum GraphRepresentation
{
	ADJACENCY_LIST = 0,
	ADJACENCY_MATRIX
};

class Graph {
public:
	Graph(GraphRepresentation style=ADJACENCY_LIST);
	virtual ~Graph();


	unsigned int AddVertex();
	//int RemoveVertex();

	unsigned int AddEdge(unsigned int startVertexId, unsigned int endVertexId);
	//int RemoveEdge();

	Vertex* GetVertex(unsigned int vertexId);
	Edge* GetEdge(unsigned int edgeId);

	void PrintVertices();
	std::string GenerateDOTDescription();
	void VisualizeDOTGraph(std::string name = "out");
	void PrintEdges();

	int SomethingToTest(float in, graph::IA* a);

private:
	unsigned int vertexCounter;
	unsigned int edgeCounter;
	const unsigned int EDGE_COUNTER_OFFSET = 1000;

	//adjacency list
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;

	unsigned int GenerateVertexId();
	unsigned int GenerateEdgeId();

};

} /* namespace graph */

#endif /* SRC_GRAPH_GRAPH_H_ */
