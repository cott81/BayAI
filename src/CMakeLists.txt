enable_testing()

include_directories("../include")

add_subdirectory(graph)
add_subdirectory(A_star)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
	#message (das)
  message(STATUS "dir='${dir}'")
endforeach()

add_executable(BayAI main.cpp)
target_link_libraries(BayAI Graph AStar)

#add_test(toDoTest toDo)

#  BayAI | dot -Tpng -o out.png; 
add_custom_target(run_graphvz BayAI | dot -Tpng -o out.png
	COMMENT "visualize graph" VERBATIM
    COMMAND gpicview out.png
	COMMENT "delete graph file" VERBATIM
    COMMAND rm out.png    
    )  