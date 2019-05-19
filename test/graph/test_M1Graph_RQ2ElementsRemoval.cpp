/*
 * test_Graph.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "graph/Graph.h"
#include "mock_A.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_; // for arbitrary mock function arguments
using ::testing::Ge;

//
// RQ2.1: Graph should return NULL for non existing vertices
//
TEST(CoolGraphImpl, RQ2_GetVerex_afterRemovalAndAdds)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();
    unsigned int idNodeD = g.AddVertex();
    unsigned int idNodeE = g.AddVertex();

    g.RemoveVertex(idNodeB);
    g.RemoveVertex(idNodeC);

    // A D E

    unsigned int idNodeF = g.AddVertex();
    unsigned int idNodeG = g.AddVertex();

    // A D E F G

    graph::Vertex* vertexPtr = g.GetVertex(idNodeD);

    if (vertexPtr == nullptr)
    {
    	// force test to fail
    	EXPECT_EQ(1, 0);
    }
    else
    {
    	EXPECT_EQ(vertexPtr->GetId(), idNodeD);
    }

}

//
// RQ2.1: Graph should be able to remove vertices [with the consequence?] such that the vertex is not any more accessible (return NULL)
//
TEST(CoolGraphImpl, RQ2_RemoveVerex_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    g.RemoveVertex(idNodeA);

    graph::Vertex* vertexPtr = g.GetVertex(idNodeA);

    EXPECT_EQ(vertexPtr, nullptr);
}


//
// RQ2.1: Graph should be able to remove vertices such that the edges from and to the vertex are also removed
//
TEST(CoolGraphImpl, RQ2_RemoveVerex_relatedEdgeElimination)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    int edgeId1 = g.AddEdge(idNodeA, idNodeB);
    int edgeId2 = g.AddEdge(idNodeB, idNodeC);

    //g.PrintEdges();

    // A -> B -> C

    g.RemoveVertex(idNodeB);

    // A should not have any edges any more
    int numEdgesA = g.GetVertex(idNodeA)->GetOutEdges().size();
    int numEdgesB = g.GetVertex(idNodeC)->GetInEdges().size();

    g.PrintEdges();

    EXPECT_EQ(numEdgesA, 0);
    EXPECT_EQ(numEdgesB, 0);
}

//
// RQ2.1: Graph should be able to remove vertices such that the edges from and to the vertex are also removed
//
TEST(CoolGraphImpl, RQ2_RemoveVerex_relatedEdgeEliminationExtended)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();
    unsigned int idNodeD = g.AddVertex();
    unsigned int idNodeE = g.AddVertex();

    unsigned int edgeId1 = g.AddEdge(idNodeA, idNodeB);
    unsigned int edgeId2 = g.AddEdge(idNodeB, idNodeC);
    unsigned int edgeId3 = g.AddEdge(idNodeA, idNodeD);
    unsigned int edgeId4 = g.AddEdge(idNodeC, idNodeD);

    // A -> B -> C
    //   -> D <-

    g.RemoveVertex(idNodeB);

    // A         C
    //   -> D <-

    // A should not have any edges any more ... no only the edge to D
    int numInEdgesA = g.GetVertex(idNodeA)->GetInEdges().size();
    int numOutEdgesA = g.GetVertex(idNodeA)->GetOutEdges().size();

    int numInEdgesC = g.GetVertex(idNodeC)->GetInEdges().size();
    int numOutEdgesC = g.GetVertex(idNodeC)->GetOutEdges().size();

    int numInEdgesD = g.GetVertex(idNodeD)->GetInEdges().size();
    int numOutEdgesD = g.GetVertex(idNodeD)->GetOutEdges().size();

    // check expected edge numbers for remaining vertices
    EXPECT_EQ(numInEdgesA, 0);
    EXPECT_EQ(numOutEdgesA, 1);
    EXPECT_EQ(numInEdgesC, 0);
    EXPECT_EQ(numOutEdgesC, 1);
    EXPECT_EQ(numInEdgesD, 2);
    EXPECT_EQ(numOutEdgesD, 0);

    // check remaing edges to point on the correct elements
    EXPECT_EQ(g.GetEdge(edgeId1), nullptr);
    EXPECT_EQ(g.GetEdge(edgeId2), nullptr);

    EXPECT_EQ(g.GetEdge(edgeId3)->GetStartVertexPtr()->GetId(), idNodeA);
    EXPECT_EQ(g.GetEdge(edgeId3)->GetEndVertexPtr()->GetId(), idNodeD);

    EXPECT_EQ(g.GetEdge(edgeId4)->GetStartVertexPtr()->GetId(), idNodeC);
    EXPECT_EQ(g.GetEdge(edgeId4)->GetEndVertexPtr()->GetId(), idNodeD);
}


//
// RQ2.1: Graph should be able to remove vertices such that all other elements are still accessible by index
//
TEST(CoolGraphImpl, RQ2_RemoveVerex_testAccessOfOtherVerticesAfterRemove_elementsBefore)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    g.RemoveVertex(idNodeB);

    graph::Vertex* vertexAPtr = g.GetVertex(idNodeA);
    unsigned int a = vertexAPtr->GetId();
    EXPECT_EQ(vertexAPtr->GetId(), idNodeA);
}

//
// RQ2.1: Graph should be able to remove vertices such that all other elements are still accessible by index
//
TEST(CoolGraphImpl, RQ2_RemoveVerex_testAccessOfOtherVerticesAfterRemove_elementsAfter)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    g.RemoveVertex(idNodeB);

    graph::Vertex* vertexCPtr = g.GetVertex(idNodeC);
    if (vertexCPtr != nullptr)
    {
    	unsigned int c = vertexCPtr->GetId();
    	EXPECT_EQ(vertexCPtr->GetId(), idNodeC);
    }
    else
    {
    	EXPECT_EQ(1, 0);
    }
}


//
// RQ2.1: Graph should be able to remove vertices such that all other elements are still accessible by index
//
TEST(CoolGraphImpl, RQ2_RemoveVerex_multipleRemove)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();
    unsigned int idNodeD = g.AddVertex();
    unsigned int idNodeE = g.AddVertex();

    g.RemoveVertex(idNodeB);
    g.RemoveVertex(idNodeA);
    g.RemoveVertex(idNodeC);
    g.RemoveVertex(idNodeD);

    EXPECT_EQ(g.GetVertex(idNodeB), nullptr);
    EXPECT_EQ(g.GetVertex(idNodeA), nullptr);
    EXPECT_EQ(g.GetVertex(idNodeC), nullptr);
    EXPECT_EQ(g.GetVertex(idNodeD), nullptr);

    // TODO: bug in implementation : ... can be that the id is bigger than the size !!!

    graph::Vertex* vertexEPtr = g.GetVertex(idNodeE);
    if (vertexEPtr != nullptr)
    {
    	unsigned int c = vertexEPtr->GetId();
    	EXPECT_EQ(vertexEPtr->GetId(), idNodeE);
    }
    else
    {
    	EXPECT_EQ(1, 0);
    }
}

//
// RQ2.2: Graph should be able to remove edges [with the consequence?]
//
TEST(CoolGraphImpl, RQ2_RemoveEdges_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    unsigned int edgeId1 = g.AddEdge(idNodeA, idNodeB);
    unsigned int edgeId2 = g.AddEdge(idNodeB, idNodeC);

    g.RemoveEdge(edgeId1);

    // check the existence
    EXPECT_EQ(g.GetEdge(edgeId1), nullptr);
    EXPECT_NE (g.GetEdge(edgeId2), nullptr);

    // no link between A->B means no outgoing edges from A and no incoming links to B
    EXPECT_EQ(g.GetVertex(idNodeA)->GetOutEdges().size(), 0);
    EXPECT_EQ(g.GetVertex(idNodeB)->GetInEdges().size(), 0);
}

//
// RQ2.2: Graph should be able to remove edges multiple edges and clean the memory 
//
TEST(CoolGraphImpl, RQ2_RemoveEdges_2RemovesOnlyOneLeft)
{
    //Found problem (segmentation fault in destructor) occurs when there is only 1 edges left after removals.
    // reason; remove function has first erasted an element -> iterator changed -> delete on _changed_ iterator
    // test stays to check this in the future. Failure -> segmentation fault in constructor

	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    unsigned int edgeId1 = g.AddEdge(idNodeA, idNodeB);
    unsigned int edgeId2 = g.AddEdge(idNodeB, idNodeC);
    unsigned int edgeId3 = g.AddEdge(idNodeA, idNodeC);

    g.RemoveEdge(edgeId1);
    g.RemoveEdge(edgeId3);

    // check the existence
    EXPECT_EQ(g.GetEdge(edgeId1), nullptr);
    EXPECT_NE (g.GetEdge(edgeId2), nullptr);
    EXPECT_EQ(g.GetEdge(edgeId3), nullptr);

    // no link between A->B and A->C means no outgoing edges from A and no incoming links to B, 1 incoming to C
    EXPECT_EQ(g.GetVertex(idNodeA)->GetOutEdges().size(), 0);
    EXPECT_EQ(g.GetVertex(idNodeB)->GetInEdges().size(), 0);
    EXPECT_EQ(g.GetVertex(idNodeC)->GetInEdges().size(), 1);        
}


