

add_library(Graph SHARED Edge.cpp Vertex.cpp)

target_include_directories(Graph PUBLIC "../../include/graph")
