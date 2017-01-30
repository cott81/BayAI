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
TEST(GraphTest, GetEdge_notExisitingEdge)
{
	graph::Graph g (graph::ADJACENCY_LIST);

	int edgeId = 0;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();

    // add edge between existing end vertices and non existing start;
    //edgeId = g.AddEdge(idNodeA, idNodeB);



    //TODO: check if the edge exists


    graph::Edge* edgePtr = g.GetEdge(2000);

    EXPECT_EQ(edgePtr, nullptr);
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
// Req: Graph should be able to remove vertices [with the consequence?]
//
TEST(GraphTest, RemoveVerex_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();

//    graph::Vertex* vertexPtr = g.GetVertex(100);

    EXPECT_EQ(0, 1);
}

//
// Req: Graph should be able to remove edges [with the consequence?]
//
TEST(GraphTest, RemoveEdges_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();

//    graph::Vertex* vertexPtr = g.GetVertex(100);

    EXPECT_EQ(0, 1);
}
