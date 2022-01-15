cmake_minimum_required(VERSION 2.6)
 
include_directories(/usr/src/gmock/include)
include_directories(/usr/src/gtest/include)
include_directories("../include")

link_directories(~/work/FunProjects/googletest/build/lib)
 
set(SRC_TESTS
	tests.cpp
	graph/test_M1Graph_RQ1ElmentsAdd.cpp
	graph/test_M1Graph_RQ2ElementsRemoval.cpp
	graph/test_M1Graph_RQ4Visualization.cpp
	#graph/A_test.cpp
	
	)
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${SRC_TESTS})
target_link_libraries(runTests  Graph gmock gtest pthread)

add_custom_target(run_tests runTests
    # run second command
    #COMMAND runTests
    )  

