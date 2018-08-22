#include <iostream>
//#include "Graph.h"

#include "GraphTest.h"
#include "Vertex.h"
#include "Edge.h"

using std::cerr;
using std::cout;
using std::endl;

#include <tuple>
#include <vector>

/*
graph::Graph generate(void);

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
*/

template <class T,  class U>
graph::GraphTest<T, U> generateTest(void)
{
  graph::GraphTest<T, U> g;

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
  //graph::Graph g = generate();
  graph::GraphTest<graph::Vertex, graph::Edge> g = generateTest < graph::Vertex, graph::Edge > ();

  //graph::GraphTest<graph::Vertex, graph::Edge> g;


  //cout << "*/" << endl; //end comment in DOT

  //cout << g.GenerateDOTDescription() << std::endl;

  //g.VisualizeDOTGraph("test");

  return 0;
}
