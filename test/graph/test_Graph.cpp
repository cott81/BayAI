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

/*
TEST(GraphTest, SomethingToTest_test)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int ret = g.SomethingToTest(1.0);
	//int ret = -1.0;
	std::cout<<"func out: " << ret << std::endl;

    EXPECT_EQ(0, ret);
}
*/


//
// Req: A graph should be able to add vertices and provide ids for them.
//
TEST(GraphTest, AddVertex_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	unsigned int vertexId = g.AddVertex();

	graph::Vertex* vertexPtr =  g.GetVertex(vertexId);

	//get the id
    EXPECT_EQ(vertexId, vertexPtr->GetId());
}

//
// Req: Vertex ids should increase with every added vertex by 1 starting with 1.
//
TEST(GraphTest, AddVertex_increasingIDs)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	unsigned int vertexId = -1;
	for (int i=0; i < 15; i++)
	{
		vertexId = g.AddVertex();
		EXPECT_EQ(i+1, vertexId);
	}
}

//
// Req: A graph should be able to define edges between two nodes. The edge should specify its start and end node.
//
TEST(GraphTest, AddEdge_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    int edgeId = g.AddEdge(idNodeA, idNodeB);

    // id generation start from 1000 + edge counter
    EXPECT_EQ(edgeId, 1001);

    // the edge should contain its start and end points
    EXPECT_EQ(g.GetEdge(edgeId)->GetStartVertexPtr()->GetId(), idNodeA);
    EXPECT_EQ(g.GetEdge(edgeId)->GetEndVertexPtr()->GetId(), idNodeB);
}

//
// Req: it should not be possible to add identical edges
//
TEST(GraphTest, AddEdge_identicalEdge)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    int edgeId = g.AddEdge(idNodeA, idNodeB);
    //try to add an identical edge to the graph
    int edgeId2 = g.AddEdge(idNodeA, idNodeB);

    EXPECT_EQ(edgeId2, graph::DUPLICATED_EDGE_ERROR);
}

//
// Req: Edges in the graph need to reference existing verices. (both not existing)
//
TEST(GraphTest, AddEdge_forBothNotExistingVertices)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

	// add edge between non existing vertices (both) on empty graph
	edgeId = g.AddEdge(1, 2);
	EXPECT_EQ(edgeId, graph::UNDEFINED_VERTEX_ERROR);
}

//
// Req: Edges in the graph need to reference existing verices. (both identical and not existing)
//
TEST(GraphTest, AddEdge_forIdenticalNotExistingVertices)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

	// add edge between non existing vertices (both identical) on empty graph
	edgeId = g.AddEdge(1, 1);
	EXPECT_EQ(edgeId, graph::IDENTICAL_EDGE_START_END_ERROR);
}

//
// Req: Edges in the graph need to reference existing verices. (not existing start)
//
TEST(GraphTest, AddEdge_forNotExistingEndVertices)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    // add edge between existing start vertices and non existing end;
    edgeId = g.AddEdge(idNodeA, 100);
    EXPECT_EQ(edgeId, graph::UNDEFINED_VERTEX_ERROR);
}

//
// Req: Edges in the graph need to reference existing verices. (not existing end)
//
TEST(GraphTest, AddEdge_forNotExistingStartVertices)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    // add edge between existing end vertices and non existing start;
    edgeId = g.AddEdge(100, idNodeA);
    EXPECT_EQ(edgeId, graph::UNDEFINED_VERTEX_ERROR);

}

//
// Req: Graph should be able to return edges
//
TEST(GraphTest, GetEdge_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    // add edge between existing end vertices and non existing start;
    edgeId = g.AddEdge(idNodeA, idNodeB);

    graph::Edge* edgePtr = g.GetEdge(edgeId);

    EXPECT_EQ(edgeId, edgePtr->GetId());
    EXPECT_EQ(idNodeA, edgePtr->GetStartVertexPtr()->GetId() );
    EXPECT_EQ(idNodeB, edgePtr->GetEndVertexPtr()->GetId() );
}

//
// Req: Graph should return NULL for non existing edges
//
TEST(GraphTest, GetEdge_notExistingEdge)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    graph::Edge* edgePtr = g.GetEdge(1001);

    EXPECT_EQ(edgePtr, nullptr);
}

//
// Req: Graph should return NULL for invalid edge id (all below the defined id offset)
//
TEST(GraphTest, GetEdge_forInvalidEdgeId)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    // add edge between existing end vertices and non existing start;
    edgeId = g.AddEdge(idNodeA, idNodeB);

    // edges have id = offset + n
    graph::Edge* edgePtr = g.GetEdge(g.GetEdgeIdOffset());

    EXPECT_EQ(edgePtr, nullptr);

    graph::Edge* edgePtr2 = g.GetEdge(g.GetEdgeIdOffset() -1);

    EXPECT_EQ(edgePtr2, nullptr);
}

//
// Req: Graph should be able to return vertices
//
TEST(GraphTest, GetVerex_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();

    graph::Vertex* vertexPtr = g.GetVertex(idNodeA);

    EXPECT_EQ(idNodeA, vertexPtr->GetId());
}

//
// Req: Graph should return NULL if there was none vertex stored
//
TEST(GraphTest, GetVerex_emptyVertexList)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    graph::Vertex* vertexPtr = g.GetVertex(100);

    EXPECT_EQ(vertexPtr, nullptr);
}

//
// Req: Graph should return NULL for non existing vertices
//
TEST(GraphTest, GetVerex_notExisitingVertex)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();

    graph::Vertex* vertexPtr = g.GetVertex(100);

    EXPECT_EQ(vertexPtr, nullptr);
}

//
// Req: Graph should return NULL for non existing vertices
//
TEST(GraphTest, GetVerex_afterRemovalAndAdds)
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
// Req: Graph should be able return a DOT description
//
TEST(GraphTest, GenerateDOTDescription_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();
    int edgeId = g.AddEdge(idNodeA, idNodeB);

    std::string generetedDOTText = g.GenerateDOTDescription();

    //expectations

    std::stringstream ss;
    ss << "digraph G {" << std::endl;
    ss << idNodeA << "->" << idNodeB << std::endl;
    ss << "}" << std::endl;
    std::string exptectedDOTText = ss.str();

    EXPECT_STREQ(generetedDOTText.c_str(), exptectedDOTText.c_str());
}

//
// Req: Graph should be able to remove vertices [with the consequence?] such that the vertex is not any more accessible (return NULL)
//
TEST(GraphTest, RemoveVerex_normal)
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
// Req: Graph should be able to remove vertices such that the edges from and to the vertex are also removed
//
TEST(GraphTest, RemoveVerex_relatedEdgeElimination)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    unsigned int idNodeA = g.AddVertex();
    unsigned int idNodeB = g.AddVertex();
    unsigned int idNodeC = g.AddVertex();

    int edgeId1 = g.AddEdge(idNodeA, idNodeB);
    int edgeId2 = g.AddEdge(idNodeB, idNodeC);

    g.PrintEdges();

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
// Req: Graph should be able to remove vertices such that the edges from and to the vertex are also removed
//
TEST(GraphTest, RemoveVerex_relatedEdgeEliminationExtended)
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

    g.PrintEdges();

    // A -> B -> C
    //   -> D <-

    g.RemoveVertex(idNodeB);

    // A should not have any edges any more
    int numInEdgesA = g.GetVertex(idNodeA)->GetInEdges().size();
    int numOutEdgesA = g.GetVertex(idNodeA)->GetOutEdges().size();

    int numInEdgesC = g.GetVertex(idNodeC)->GetInEdges().size();
    int numOutEdgesC = g.GetVertex(idNodeC)->GetOutEdges().size();

    int numInEdgesD = g.GetVertex(idNodeD)->GetInEdges().size();
    int numOutEdgesD = g.GetVertex(idNodeD)->GetOutEdges().size();

    g.PrintEdges();

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


    //TODO: fix this ...

    graph::Edge* e = g.GetEdge(edgeId4);
    graph::Vertex* v = e->GetStartVertexPtr();

    EXPECT_EQ(g.GetEdge(edgeId4)->GetStartVertexPtr()->GetId(), idNodeC);
    EXPECT_EQ(g.GetEdge(edgeId4)->GetEndVertexPtr()->GetId(), idNodeD);
}


//
// Req: Graph should be able to remove vertices such that all other elements are still accessible by index
//
TEST(GraphTest, RemoveVerex_testAccessOfOtherVerticesAfterRemove_elementsBefore)
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
// Req: Graph should be able to remove vertices such that all other elements are still accessible by index
//
TEST(GraphTest, RemoveVerex_testAccessOfOtherVerticesAfterRemove_elementsAfter)
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
// Req: Graph should be able to remove vertices such that all other elements are still accessible by index
//
TEST(GraphTest, RemoveVerex_multipleRemove)
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
// Req: Graph should be able to remove edges [with the consequence?]
//
TEST(GraphTest, RemoveEdges_normal)
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
