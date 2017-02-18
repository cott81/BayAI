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
// RQ4: Graph should be able return a DOT description
//
TEST(CoolGraphImpl, RQ4_GenerateDOTDescription_normal)
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

