#include <iostream>
#include "Graph.h"

  using std::cerr;
  using std::cout;
  using std::endl;

#include <tuple>
#include <vector>


int main(int    argc, char** argv)
{
    cout << "Test Application: ..." << endl;

    graph::Graph g;

    int idNodeA = g.AddVertex();
    int idNodeB = g.AddVertex();
    int idNodeC = g.AddVertex();

    g.PrintVertices();



    g.AddEdge(idNodeA, idNodeB);
    g.AddEdge(idNodeA, idNodeC);
    g.AddEdge(idNodeB, idNodeC);

    g.PrintEdges();

    g.GetVertex(idNodeA)->PrintOutEdges();
    cout << g.GetVertex(idNodeA)->GetOutEdges()[1]->GetId() << endl;

    return 0;
}

