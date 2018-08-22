cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
#find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#include_directories(${GMOCK_INCLUDE_DIRS})

#set (GMOCK_INCLUDE_DIRS /usr/lib/libgmock.a )

#message ("GTest: " ${GTEST_INCLUDE_DIRS} ${GTEST_LIBRARIES})
#message ("GMock: " ${GMOCK_INCLUDE_DIRS} ${GMOCK_LIBRARIES})

include_directories(~/work/FunProjects/googletest/googlemock/include)
include_directories(~/work/FunProjects/googletest/googletest/include)
include_directories("../include")

link_directories(~/work/FunProjects/googletest/build/googlemock ~/work/FunProjects/googletest/build/googlemock/gtest)
 
set(SRC_TESTS
	tests.cpp
	graph/test_M1Graph_RQ1ElmentsAdd.cpp
	#graph/test_M1Graph_RQ2ElementsRemoval.cpp
	#graph/test_M1Graph_RQ4Visualization.cpp
	#graph/A_test.cpp
	
	)
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${SRC_TESTS})
#${GMOCK_LIBRARIES}
#target_link_libraries(runTests Graph ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES}  pthread)
#Graph
target_link_libraries(runTests  Graph gmock gtest pthread)

#add_dependencies(check runTests)

add_custom_target(run_tests runTests
    # run second command
    #COMMAND runTests
    )  

