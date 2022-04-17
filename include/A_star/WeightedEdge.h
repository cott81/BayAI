/*
 * Link.h
 *
 * Copyright Feb 26, 2016 Dominik Kirchner
 */

#ifndef WEIGHTEDEDGE_H_
#define WEIGHTEDEDGE_H_

#include "Edge.h"
#include "Vertex.h"

namespace a_star {

class WeightedEdge 
	: public graph::Edge 
{

public:
	WeightedEdge(graph::Vertex* origin, graph::Vertex* goal, unsigned int edgeId, double edgeWeight=1.0);
	//WeightedEdge();
	virtual ~WeightedEdge();

	unsigned int AddWeight(double edgeWeight);
	double GetWeight(void) {return this->weight;};

protected:
	double weight;

};

} /* namespace a_star */

#endif /* WEIGHTEDEDGE_H_ */
