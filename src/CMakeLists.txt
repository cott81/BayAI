enable_testing()

include_directories("../include")

add_subdirectory(graph)
#add_subdirectory(fancyLib)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
	#message (das)
  message(STATUS "dir='${dir}'")
endforeach()

add_executable(BayAI main.cpp)
target_link_libraries(BayAI Graph)

#add_test(toDoTest toDo)