/*
 * WeightedGraph.cpp
 *
 * Copyright Jan 15, 2021 Dominik Kirchner
 */

#include "WeightedGraph.h"
#include <iostream>
#include <sstream>
#include "Vertex.h"
#include "WeightedEdge.h"

namespace a_star 
{

    WeightedGraph::WeightedGraph() 
    {

    }
    
    WeightedGraph::~WeightedGraph() 
    {
        
    }

    void WeightedGraph::PrintEdges()
    {
        std::cout << "WeightedGraph: Print edges for graph:" << std::endl;
        for(graph::Edge* e : this->edges)
        {
            //cast to weightedEdge
            WeightedEdge* we = static_cast<WeightedEdge*> (e);
            std::cout << "\t id: " << we->GetId() << ": " << we->GetStartVertexPtr()->GetId() << " -> " << we->GetEndVertexPtr()->GetId() << ": w=" << we->GetWeight()  << std::endl;
        }
    }

    int WeightedGraph::AddEdge(unsigned int startVertexId, unsigned int endVertexId, double edgeWeight)
    {
        //temp store the edge weight in object to use it in GenerateEdgeFrom()
        this->tempEdgeWeight = edgeWeight;

        //call base AddEdge call  -> GenerateEdgeFrom() is overriten and a weighted edged is generated
        int edgeId = graph::Graph::AddEdge(startVertexId, endVertexId);

        return edgeId;
    }

    graph::Edge* WeightedGraph::GenerateEdgeFrom(unsigned int startVertexId, unsigned int endVertexId, unsigned int edgeId)
    {     
        graph::Edge* ePtr = new WeightedEdge (GetVertex(startVertexId), GetVertex(endVertexId), edgeId, this->tempEdgeWeight);
        
        return ePtr;
    }

    std::string WeightedGraph::GenerateDOTDescription()
    {
        // build the string
        std::stringstream ss;
        ss << "digraph G {" << std::endl;

        for(graph::Edge* e : this->edges)
        {
            WeightedEdge* we = static_cast<WeightedEdge*> (e);
            // A -> B [label = "0.1"]
            ss << we->GetStartVertexPtr()->GetId() << "->" << we->GetEndVertexPtr()->GetId();
            ss << " [label = \"" << we->GetWeight() << "\"]" << std::endl;
        }

        ss << "}" << std::endl;

        return ss.str();
    }

}