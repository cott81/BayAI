
set (A_STAR_SRC 
	WeightedEdge.cpp 
	)

add_library(AStar SHARED ${A_STAR_SRC})

target_include_directories(AStar PUBLIC "../../include/A_star")
target_include_directories(AStar PUBLIC "../../include/graph")
