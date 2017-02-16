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

	return vertexId;
}

Vertex* Graph::GetVertex(unsigned int vertexId)
{
	// vertexId starts with 1 -> vector index needs to be vertexId -1
	graph::Vertex* vertexPtr = nullptr;

	unsigned int vertexIdx = vertexId - 1;


	// no elemets in the vector
	if ((unsigned int)this->vertices.size() == 0)
	{
		std::cerr << "Graph: ERROR: Vertex is empty. Return NULL." << std::endl;
		vertexPtr = nullptr;
	}
	// we have an ordered list. End element has always biggest id
	else if ( vertexId > this->vertices.back().GetId() )
	{
		//id is not yet added
		std::cerr << "Graph: ERROR: vertex with id " << vertexId << " is not yet added to the graph. Return NULL." << std::endl;
		vertexPtr = nullptr;
	}
	else
	{
		// use an iterator
		std::vector<Vertex>::iterator startIter;

		// check if the idx can directly be used (id last element could be bigger as available elements in vector)
		if ((unsigned int) this->vertices.size() > (vertexIdx + 1) )
		{
			startIter = this->vertices.begin() + vertexIdx;
		}
		else
		{
			startIter = this->vertices.end();
		}

		// iterate through vector beginning from the expected element location (startIter) towards the beginning
		std::vector<Vertex>::iterator it;
		for(it= startIter; it >= this->vertices.begin(); it-- )
		{
		    // element found
		    if((*it).GetId() == vertexId)
		    {
		    	vertexPtr = &*it;
		        break;
		    }
		}
	}

	return vertexPtr;
}

int Graph::RemoveVertex(unsigned int vertexId)
{
	int returnCode = UNSPECIFIED_ERROR;

	unsigned int vertexIdx = vertexId - 1;

	// check that there are at least as many elements in the vector as the requested vertexId
	if ((unsigned int)this->vertices.size() < vertexId)
	{
		//id is not yet added
		std::cerr << "Graph: ERROR: vertex with id " << vertexId << " is not yet added to the graph. Return NULL." << std::endl;
		returnCode = UNSPECIFIED_ERROR;
	}
	// check if the element is directly at the position (prev removes may have changed the position
	else if (this->vertices[vertexIdx].GetId() == vertexId)
	{

		RemoveVertexEdges(this->vertices[vertexIdx]);

		//TODO: update remaining edges

		// only a single element is removed ... all elements with an id bigger than this needs to point to an index earlier

		//for (Edge e : this->edges)
		for (int i= 0; i<this->edges.size(); i++)
		{
			// this makes the edges point shortly to wrong vertices until the vertex is removed!!!
			if (this->edges[i].GetStartVertexPtr()->GetId() > vertexIdx )
			{
				// update pointer: point to the previous element
				this->edges[i].DecreaseStartVertexPtr();
			}
			if (this->edges[i].GetEndVertexPtr()->GetId() > vertexIdx )
			{
				// update pointer: point to the previous element
				this->edges[i].DecreaseEndVertexPtr();
			}
		}

		//TODO: perhaps simply set elemet->id to invalid ...
		this->vertices.erase(this->vertices.begin() + vertexIdx);
		returnCode = 0;
	}
	// element not at original position
	else
	{
		// use an iterator
		 std::vector<Vertex>::iterator startIter = this->vertices.begin() + vertexIdx;

		// iterate through vector beginning from the expected element location (startIter) towards the beginning
		std::vector<Vertex>::iterator it;
		for(it= startIter; it >= this->vertices.begin(); it-- )
		{
		    // element found
		    if((*it).GetId() == vertexId)
		    {
		    	//remove all edges in which the vertex "it" is involved
		    	RemoveVertexEdges(*it);

		    	//TODO: update remaining edges

		    	// remove found element
		    	this->vertices.erase(it);
		        break;
		    }
		}
	}

	return returnCode;
}

graph::Edge* Graph::GetEdge(unsigned int edgeId)
{
	graph::Edge* edgePtr = nullptr;

	// check that the id is in general valid
	if (edgeId <= EDGE_COUNTER_OFFSET)
	{
		std::cerr << "Graph: ERROR: The given id " << edgeId << " is invalid. Edge ids start with " << (EDGE_COUNTER_OFFSET + 1) <<  std::endl;
		return nullptr;
	}
	// defined an offset of 1000
	// first edge has id 1001. substract the offset and 1 to start with idx 0 of the vector
	unsigned int edgeIdx = edgeId - EDGE_COUNTER_OFFSET -1;

	// check if the vector is empty
	if ((unsigned int)this->edges.size() == 0)
	{
		// element is not yet added
		std::cerr << "Graph: ERROR: Edge is empty. Return NULL." << std::endl;
		return nullptr;
	}

	// we have an ordered list. End element has always biggest id
	if ( edgeId > this->edges.back().GetId() )
	{
		//id is not yet added
		std::cerr << "Graph: ERROR: edges with id " << edgeId << " is not yet added to the graph. Return NULL." << std::endl;
		edgePtr = nullptr;
	}
	else
	{
		// use an iterator
		std::vector<Edge>::iterator startIter;

		// check if the idx can directly be used (id last element could be bigger as available elements in vector)
		if ((unsigned int) this->edges.size() > (edgeIdx + 1) )
		{
			startIter = this->edges.begin() + edgeIdx;
		}
		else
		{
			startIter = this->edges.end();
		}

		// iterate through vector beginning from the expected element location (startIter) towards the beginning
		std::vector<Edge>::iterator it;
		for(it= startIter; it >= this->edges.begin(); it-- )
		{
		    // element found
		    if((*it).GetId() == edgeId)
		    {
		    	edgePtr = &*it;
		        break;
		    }
		}
	}

	return edgePtr;

}

int Graph::AddEdge(unsigned int startVertexId, unsigned int endVertexId)
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
		return IDENTICAL_EDGE_START_END_ERROR;
	}

	if ((unsigned int)this->vertices.size() < idToCheck )
	{
		// use the fact that ids are the place the vector
		std::cerr << "Graph: ERROR: vertex id: " << idToCheck << "is not yet defined" << std::endl;
		return UNDEFINED_VERTEX_ERROR;
	}

	// store the edge in graph's edge list
	unsigned int edgeId = GenerateEdgeId();
	Edge e(GetVertex(startVertexId), GetVertex(endVertexId), edgeId);

	// store edge object on vector
	this->edges.push_back(e);

	// get the adress from the stored object in the vector
	Edge* ePtr = GetEdge(edgeId);

	//check if there is already a same edge in the list by checking the vertices and their incoming and outgoing edges
	// link vertices (add entries to the vertices data structures)
	if (GetVertex(startVertexId)->AddOutgoingEdge(ePtr) == -1)
	{
		std::cerr << "Graph: ERROR: Outgoing Edge for vertex id: " << startVertexId << "to "<< endVertexId<<" already exists." << std::endl;
		//TODO remove the edge from vector
		return DUPLICATED_EDGE_ERROR;
	}

	if (GetVertex(endVertexId)->AddIncomingEdge(ePtr) == -1)
	{
		std::cerr << "Graph: ERROR: Incoming Edge for vertex id: " << endVertexId << "from "<< startVertexId <<" already exists." << std::endl;
		//TODO remove the edge from vector
		return DUPLICATED_EDGE_ERROR;
	}


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

int Graph::RemoveVertexEdges(graph::Vertex& v)
{
	int returnCode = 0;
	//remove all edges in which the vertex it is involved

	// remove edges outgoing for vertex (it)
	for (auto edgePtr : v.GetOutEdges())
	{
		//get vertex for outgoing edge of it and remove its corresponding incoming edge (double connected list)
		edgePtr->GetEndVertexPtr()->RemoveIncomingEdge(v.GetId());
	}

	// remove edges incoming
	for (auto edgePtr : v.GetInEdges())
	{
		//get vertex for incoming edge of it and remove its corresponding outgoing edge (double connected list)
		edgePtr->GetStartVertexPtr()->RemoveOutgoingEdge(v.GetId());
	}

	// remove edge element (stored in graph)
	for (auto it2 = this->edges.begin(); it2 < this->edges.end(); ++it2)
	{
		if (it2->GetStartVertexPtr()->GetId() == v.GetId()  || it2->GetEndVertexPtr()->GetId() == v.GetId())
		{
			this->edges.erase(it2);
			//update iterator: point to the last valid element such that the increment is able to point to the following element
			it2--;
		}
	}

	return returnCode;
}

int Graph::SomethingToTest(float in)
{
	if (in > 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}



} /* namespace graph */

