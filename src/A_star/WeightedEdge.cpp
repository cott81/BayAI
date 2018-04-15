/*
 * WeightedEdge.cpp
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#include "WeightedEdge.h"

namespace a_star {

WeightedEdge::WeightedEdge(graph::Vertex* origin, graph::Vertex* goal, double edgeWeight) : graph::Edge(origin, goal) {

    this->weight = edgeWeight;
}

WeightedEdge::~WeightedEdge() {
}

unsigned int WeightedEdge::AddWeight(double edgeWeight)
{
    this->weight = edgeWeight;

    //TODO: add error code
    return 0;
}

} /* namespace bayes_net */