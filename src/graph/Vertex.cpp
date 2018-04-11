/*
 * Vertex.cpp
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#include "Vertex.h"

#include <iostream>

namespace graph {


Vertex::Vertex(unsigned int id) {
//	std::cout << "Vertex: DEBUG: create vertex with id: "<< id << std::endl;
	this->id = id;
}

Vertex::~Vertex() {
}

int Vertex::AddIncomingEdge(Edge* incomingEdgePtr)
{
	//check if it is really an incoming edge
	if (incomingEdgePtr->GetEndVertexPtr()->GetId() != this->id)
	{
		std::cerr << "Vertex::AddIncomingEdge(): ERROR: given edge pointer to store as a incoming edge end vertecx id: "
				<< incomingEdgePtr->GetEndVertexPtr()->GetId() << " does not match this id: " << this->id << std::endl;
	}

	//check if it is already in the list
	//TODO: sort the vector after the id of the parent vertex -> need only to iterate until a higher id is found.
	for (Edge* ePtr : this->in_edges)
	{
		if (
				( ePtr->GetStartVertexPtr()->GetId() == incomingEdgePtr->GetStartVertexPtr()->GetId() )
				&& ( ePtr->GetEndVertexPtr()->GetId() == incomingEdgePtr->GetEndVertexPtr()->GetId() )
			)
		{
			std::cerr << "Vertex::AddIncomingEdge(): Error: edge already stored." << std::endl;
			return -1;
		}
	}

	this->in_edges.push_back(incomingEdgePtr);

	return 0;
}

int Vertex::RemoveIncomingEdge(unsigned int originVertexId)
{
	// check if the originVertex is own id
	if (originVertexId == this->id)
	{
		std::cerr << "Vertex::RemoveIncomingEdge(): ERROR: given edge start vertex id shall not be identical to the id of this vertex" << std::endl;
		return -1;
	}


	std::vector<graph::Edge*>::iterator it;
	for (it = this->in_edges.begin(); it < this->in_edges.end(); it++)
	{
		if ((*it)->GetStartVertexPtr()->GetId() == originVertexId )
		{
			this->in_edges.erase(it);
			return 0;
		}
	}

	return 0;
}

int Vertex::AddOutgoingEdge(Edge* outgoingEdgePtr)
{
	//check if it is really an outgoing edge
	if (outgoingEdgePtr->GetStartVertexPtr()->GetId() != this->id)
	{
		std::cout << "Vertex::AddOutgoingEdge(): ERROR: given edge pointer to store as an outgoing edge start vertex id: "
				<< outgoingEdgePtr->GetStartVertexPtr()->GetId() << " does not match this id: " << this->id << std::endl;
		return -1;
	}

	//check if it is already in the list
	//TODO: sort the vector after the id of the parent vertex -> need only to iterate until a higher id is found.
	for (Edge* ePtr : this->out_edges)
	{
		if (
				( ePtr->GetStartVertexPtr()->GetId() == outgoingEdgePtr->GetStartVertexPtr()->GetId() )
				&& ( ePtr->GetEndVertexPtr()->GetId() == outgoingEdgePtr->GetEndVertexPtr()->GetId() )
			)
		{
			std::cerr << "Vertex::AddOutgoingEdge(): ERROR: edge already stored. Do not add it again." << std::endl;
			return -1;
		}
	}

	this->out_edges.push_back(outgoingEdgePtr);

	return 0;
}

int Vertex::RemoveOutgoingEdge(unsigned int endVertexId)
{
	// check if the originVertex is own id
	if (endVertexId == this->id)
	{
		std::cerr << "Vertex::RemoveOutgoingEdge(): ERROR: given edge end vertex id shall not be identical to the id of this vertex" << std::endl;
		return -1;
	}


	std::vector<graph::Edge*>::iterator it;
	for (it = this->out_edges.begin(); it < this->out_edges.end(); it++)
	{
		if ((*it)->GetEndVertexPtr()->GetId() == endVertexId)
		{
			this->out_edges.erase(it);
			return 0;
		}
	}

	return 0;
}

int Vertex::PrintInEdges()
{
	std::cout << "Vertex::PrintEdges(): incoming for vertex: "<< this->id << std::endl;
	for (Edge* ePtr: this->in_edges)
	{
		std::cout << "\t" << ePtr->GetStartVertexPtr()->GetId() << " -> " << ePtr->GetEndVertexPtr()->GetId() << std::endl;
	}
	return 0;
}

int Vertex::PrintOutEdges()
{
	std::cout << "Vertex::PrintEdges(): outgoing for vertex: "<< this->id << std::endl;
	for (Edge* ePtr: this->out_edges)
	{
		std::cout << "\t" << ePtr->GetStartVertexPtr()->GetId() << " -> " << ePtr->GetEndVertexPtr()->GetId() << std::endl;
	}
	return 0;
}


} /* namespace graph */
