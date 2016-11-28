/*
 * Graph.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: dominik
 */

#include "Graph.h"

#include <iostream>
#include <sstream>
#include <stdlib.h> //system
#include <fstream> //ofstream

#include "A.h"


namespace graph
{

Graph::Graph(GraphRepresentation style)
{
	if (style == ADJACENCY_LIST)
	{
		this->vertexCounter = 0;
		this->edgeCounter = EDGE_COUNTER_OFFSET;
	}
	else if (style == ADJACENCY_MATRIX)
	{
		//TODO: add the adjacency matrix presentation
		std::cout << "Graph(): adjacency matrix representation is not yet implemented. " << std::endl;
	}
	else
	{
		std::cerr << "Graph(): FAILURE: graph presentation style: %d is not supported." << std::endl;
	}


}


Graph::~Graph()
{

}

unsigned int Graph::GenerateVertexId()
{
	// ids starts with 1; 0 is preserved for an unvalid id;
	unsigned int newVertexId = ++this->vertexCounter;
	return newVertexId;
}

unsigned int Graph::GenerateEdgeId()
{
	unsigned int newEdgeId = ++this->edgeCounter;
	return newEdgeId;
}

unsigned int Graph::AddVertex()
{
	int vertexId = GenerateVertexId();

	Vertex v(vertexId);
	this->vertices.push_back(v);

	std::cout << "Graph: DEBUG: created vertex with id: " << vertexId << std::endl;

	return vertexId;
}

Vertex* Graph::GetVertex(unsigned int vertexId)
{
	//makes the assumption that the vertexId is the vector index
	// vertexId starts with 1 -> vector index needs to be vertexId -1
	unsigned int vertexIdx = vertexId - 1;
	return &(this->vertices[vertexIdx]);
}

Edge* Graph::GetEdge(unsigned int edgeId)
{
	// defined an offset of 1000
	// first edge has id 1001. substract the offset and 1 to start with idx 0 of the vector
	unsigned int edgeIdx = edgeId - EDGE_COUNTER_OFFSET -1;
	return &(this->edges[edgeIdx]);
}

unsigned int Graph::AddEdge(unsigned int startVertexId, unsigned int endVertexId)
{
	// error checks: check if vertices are already defined
	// TODO: if remove of vertices are allowed this needs some refinement!
	unsigned int idToCheck;
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

	if ((unsigned int)this->vertices.size() < idToCheck )
	{
		// use the fact that ids are the place the vector
		std::cerr << "Graph: ERROR: vertex id: " << idToCheck << "is not yet defined" << std::endl;
		return -1;
	}

	//TODO: check if there is already a same edge in the list

	// store the edge in graph's edge list
	//Edge e(&(this->vertices[startVertexId]), &(this->vertices[endVertexId]), this->edgeCounter);
	unsigned int edgeId = GenerateEdgeId();
	Edge e(GetVertex(startVertexId), GetVertex(endVertexId), edgeId);
	this->edges.push_back(e);


	// get the adress from the stored object in the vector

	Edge* ePtr = GetEdge(edgeId);

	// link vertices (add entries to the vertices data structures)
	GetVertex(startVertexId)->AddOutgoingEdge(ePtr);
	GetVertex(endVertexId)->AddIncomingEdge(ePtr);


	std::cout << "Graph::AddEdge(): DEBUG: created edge between (start) id: " << startVertexId
			<< " and (end) id: "<< endVertexId <<  std::endl;

	return edgeId;
}

void Graph::PrintVertices()
{
	std::cout << "Print vertices for graph:" << std::endl;
	for(Vertex v : this->vertices)
	{
		std::cout << "\t" << v.GetId() << std::endl;
	}
}

std::string Graph::GenerateDOTDescription()
{
	// build the string
	std::stringstream ss;

	ss << "digraph G {" << std::endl;

	for(Edge e : this->edges)
	{
		ss << e.GetStartVertexPtr()->GetId() << "->" << e.GetEndVertexPtr()->GetId() << std::endl;
	}

	ss << "}" << std::endl;

	return ss.str();
}

void Graph::VisualizeDOTGraph(std::string name)
{
	std::string dotDesc = GenerateDOTDescription();

	std::ofstream dotFile;
	dotFile.open("graphDef.gv");
	dotFile << dotDesc;
	dotFile.close();

	std::string dotCmd = "dot -Tpng graphDef.gv -o " + name +".png";
	system(dotCmd.c_str());
	std::string showCmd = "gpicview "+ name + ".png &";
	system(showCmd.c_str());
	return;
}

void Graph::PrintEdges()
{
	std::cout << "Print edges for graph:" << std::endl;
	for(Edge e : this->edges)
	{
		std::cout << "\t id: " << e.GetId() << ": " << e.GetStartVertexPtr()->GetId() << " -> " << e.GetEndVertexPtr()->GetId() << std::endl;
	}
}


int Graph::SomethingToTest(float in, IA* a)
{
	//some call
	//IA* a = new A();
	int ret = a->testFunction(1);

	std::cout << "graph::testFunc(1) = " << ret << std::endl;

	if (in > 0)
	{
		return ret;
	}
	else
	{
		return -1;
	}
}



} /* namespace graph */

