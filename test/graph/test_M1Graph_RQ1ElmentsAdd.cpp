/*
 * test_Graph.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: dominik
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "graph/Graph.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_; // for arbitrary mock function arguments
using ::testing::Ge;

//
// RQ1.1: A graph should be able to add vertices and provide ids for them.
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
// RQ1.1: Vertex ids should increase with every added vertex by 1 starting with 1.
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
// RQ1.2: A graph should be able to define edges between two nodes. The edge should specify its start and end node.
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
// RQ1.2: it should not be possible to add identical edges
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
// RQ1.2: Edges in the graph need to reference existing verices. (both not existing)
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
// RQ1.2: Edges in the graph need to reference existing verices. (both identical and not existing)
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
// RQ1.2: Edges in the graph need to reference existing verices. (not existing start)
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
// RQ1.2: Edges in the graph need to reference existing verices. (not existing end)
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
// RQ: Graph should be able to return edges
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
// RQ: Graph should return NULL for non existing edges
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
// RQ: Graph should return NULL for invalid edge id (all below the defined id offset)
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
// RQ: Graph should be able to return vertices
//
TEST(GraphTest, GetVerex_normal)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();

    graph::Vertex* vertexPtr = g.GetVertex(idNodeA);

    EXPECT_EQ(idNodeA, vertexPtr->GetId());
}

//
// RQ: Graph should return NULL if there was none vertex stored
//
TEST(GraphTest, GetVerex_emptyVertexList)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    graph::Vertex* vertexPtr = g.GetVertex(100);

    EXPECT_EQ(vertexPtr, nullptr);
}

//
// RQ: Graph should return NULL for non existing vertices
//
TEST(GraphTest, GetVerex_notExisitingVertex)
{
	graph::Graph g (graph::ADJACENCY_LIST);

    int idNodeA = g.AddVertex();

    graph::Vertex* vertexPtr = g.GetVertex(100);

    EXPECT_EQ(vertexPtr, nullptr);
}
