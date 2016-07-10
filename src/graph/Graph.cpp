/*
 * Graph.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: dominik
 */

#include "Graph.h"

#include <iostream>

namespace graph
{
Graph::Graph() {
	this->vertexCounter = 0;
	this->edgeCounter = EDGE_COUNTER_OFFSET;
}

Graph::~Graph()
{

}

unsigned int Graph::GenerateVertexId()
{
	unsigned int newVertexId = this->vertexCounter++;
	return newVertexId;
}

unsigned int Graph::GenerateEdgeId()
{
	unsigned int newVertexId = this->vertexCounter++;
	return newVertexId;
}

int Graph::AddVertex()
{
	int vertexId = this->vertexCounter;

	Vertex v(vertexId);
	this->vertices.push_back(v);

	std::cout << "Graph: DEBUG: created vertex with id: " << vertexId << std::endl;

	//increase vertex id counter
	this->vertexCounter++;

	return vertexId;
}

int Graph::AddEdge(int startVertexId, int endVertexId)
{
	// error checks: check if vertices are already defined
	int idToCheck;
	if (startVertexId > endVertexId)
	{
		idToCheck = startVertexId;
	}
	else if (endVertexId > startVertexId)
	{
		idToCheck = endVertexId;
	}
	else
	{
		std::cerr << "Graph: ERROR: start and end of the edge are identical: " << startVertexId << std::endl;
		std::cerr << "Graph: ERROR: do not add this edge" << std::endl;
		return -1;
	}

	if ((int)this->vertices.size() < idToCheck )
	{
		// use the fact that ids are the place the vector
		std::cerr << "Graph: ERROR: vertex id: " << idToCheck << "is not yet defined" << std::endl;
		return -1;
	}

	//TODO: check if there is already a same edge in the list

	// store the edge in graph's edge list
	Edge e(&(this->vertices[startVertexId]), &(this->vertices[endVertexId]), this->edgeCounter);
	this->edges.push_back(e);


	// get the adress from the stored object in the vector

	//HACK: edge ids start with 1000
	Edge* ePtr = &(this->edges[this->edgeCounter - EDGE_COUNTER_OFFSET]);

	// link vertices (add entries to the vertices data structures)
	this->vertices[startVertexId].AddOutgoingEdge(ePtr);
	this->vertices[endVertexId].AddIncomingEdge(ePtr);


	std::cout << "Graph::AddEdge(): DEBUG: created edge between (start) id: " << startVertexId
			<< " and (end) id: "<< endVertexId <<  std::endl;

	int temp_edgeId = this->edgeCounter;

	//increase edge id counter
	this->edgeCounter++;

	return temp_edgeId;
}

Vertex* Graph::GetVertex(unsigned int vertexId)
{
	//makes the assumption that the vertexId is the vector index
	return &(this->vertices[vertexId]);
}

void Graph::PrintVertices()
{
	std::cout << "Print vertices for graph:" << std::endl;
	for(Vertex v : this->vertices)
	{
		std::cout << "\t" << v.GetId() << std::endl;
	}
}

void Graph::PrintEdges()
{
	std::cout << "Print edges for graph:" << std::endl;
	for(Edge e : this->edges)
	{
		std::cout << "\t id: " << e.GetId() << ": " << e.GetStartVertexPtr()->GetId() << " -> " << e.GetEndVertexPtr()->GetId() << std::endl;
	}
}

} /* namespace graph */

