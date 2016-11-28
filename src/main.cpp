#include <iostream>
#include "Graph.h"

  using std::cerr;
  using std::cout;
  using std::endl;

#include <tuple>
#include <vector>


int main(int    argc, char** argv)
{
	cout << "/*" << endl; // start comment for DOT
    cout << "Test Application: ..." << endl;

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



    cout << "*/" << endl; //end comment in DOT

    cout << g.GenerateDOTDescription() << std::endl;

    g.VisualizeDOTGraph();

    g.VisualizeDOTGraph("test");


    return 0;
}

