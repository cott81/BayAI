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


namespace graph {

enum GraphRepresentation
{
	ADJACENCY_LIST = 0,
	ADJACENCY_MATRIX
};

enum GraphErrors
{
	UNSPECIFIED_ERROR = -1,
	IDENTICAL_EDGE_START_END_ERROR = -2,
	UNDEFINED_VERTEX_ERROR = -3,
	DUPLICATED_EDGE_ERROR = -4
};

class Graph {
public:
	Graph(GraphRepresentation style=ADJACENCY_LIST);
	virtual ~Graph();


	unsigned int AddVertex();
	int RemoveVertex(unsigned int vertexId);

	int AddEdge(unsigned int startVertexId, unsigned int endVertexId);
	int RemoveEdge(unsigned int edgeId);

	Vertex* GetVertex(unsigned int vertexId);
	Edge* GetEdge(unsigned int edgeId);

	std::string GenerateDOTDescription();
	void VisualizeDOTGraph(std::string name = "out");

	void PrintVertices();
	void PrintEdges();

	int SomethingToTest(float in);

	inline const unsigned int GetEdgeIdOffset(void){return EDGE_COUNTER_OFFSET;};

private:
	unsigned int vertexCounter;
	unsigned int edgeCounter;
	const unsigned int EDGE_COUNTER_OFFSET = 1000;

	//adjacency list
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;

	inline unsigned int GenerateVertexId();
	inline unsigned int GenerateEdgeId();
	int RemoveVertexEdges(graph::Vertex& v);
	int UpdateRemaingEdgesAfterVertexRemoval(unsigned int vertexId);

};

} /* namespace graph */

#endif /* SRC_GRAPH_GRAPH_H_ */
