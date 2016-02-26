cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("BayAI")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_subdirectory(src)
add_subdirectory(test)
                    
