#include <iostream>
#include "Graph.h"
#include "A_star/WeightedGraph.h"

using std::cerr;
using std::cout;
using std::endl;

#include <tuple>
#include <vector>

graph::Graph generate(void);

// generate function for a weighted graph
graph::Graph* generateWeighted(void);

graph::Graph* generateWeighted(void)
{
  a_star::WeightedGraph* wgPtr = new a_star::WeightedGraph();

  int idNodeA = wgPtr->AddVertex();
  int idNodeB = wgPtr->AddVertex();
  int idNodeC = wgPtr->AddVertex();
  int idNodeD = wgPtr->AddVertex();

  wgPtr->PrintVertices();

  wgPtr->AddEdge(idNodeA, idNodeB, 0.75);
  wgPtr->AddEdge(idNodeA, idNodeC, 0.5);
  wgPtr->AddEdge(idNodeC, idNodeD, 0.1);
  wgPtr->AddEdge(idNodeB, idNodeD, 0.9);

  wgPtr->PrintEdges();

  graph::Graph* gPtr = static_cast<graph::Graph*>(wgPtr);

  return gPtr;
}

graph::Graph generate(void)
{
  graph::Graph g(graph::ADJACENCY_LIST);

  int idNodeA = g.AddVertex();
  int idNodeB = g.AddVertex();
  int idNodeC = g.AddVertex();
  int idNodeD = g.AddVertex();

  g.PrintVertices();

  g.AddEdge(idNodeA, idNodeB);
  g.AddEdge(idNodeA, idNodeC);
  g.AddEdge(idNodeB, idNodeC);
  g.AddEdge(idNodeC, idNodeD);

  g.PrintEdges();

  g.GetVertex(idNodeA)->PrintOutEdges();
  cout << g.GetVertex(idNodeA)->GetOutEdges()[1]->GetId() << endl;

  return g;
}

int main(int argc, char **argv)
{
  cout << "/*" << endl; // start comment for DOT
  cout << "Test Application: ..." << endl;

  // generate data structure ...
  // graph::Graph g = generate();
  // graph::Graph* gPtr = &g;
  graph::Graph* gPtr = generateWeighted();

  cout << "*/" << endl; //end comment in DOT

  cout << gPtr->GenerateDOTDescription() << std::endl;

  gPtr->VisualizeDOTGraph("test");

  return 0;
}