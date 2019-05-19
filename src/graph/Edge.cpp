/*
 * Edge.cpp
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#include "Edge.h"
#include "Vertex.h"

#include <iostream>

namespace graph {

Edge::Edge(Vertex* originPtr, Vertex* goalPtr, unsigned int edgeId)
{
	this->link.first = originPtr;
	this->link.second = goalPtr;
	this->id = edgeId;
}

Edge::~Edge() 
{
}

} /* namespace graph */
