/*
 * WeightedEdge.cpp
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#include "WeightedEdge.h"

namespace a_star {

WeightedEdge::WeightedEdge(graph::Vertex* origin, graph::Vertex* goal, unsigned int edgeId, double edgeWeight) 
    : graph::Edge(origin, goal, edgeId)
{

    this->weight = edgeWeight;
}

WeightedEdge::~WeightedEdge() {
}

unsigned int WeightedEdge::AddWeight(double edgeWeight)
{
    this->weight = edgeWeight;
    return 0;
}

} /* namespace a_star */