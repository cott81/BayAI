
set (GRAPH_SRC 
	Edge.cpp 
	Vertex.cpp
	Graph.cpp
	)

add_library(Graph SHARED ${GRAPH_SRC})

target_include_directories(Graph PUBLIC "../../include/graph")
