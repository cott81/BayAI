#cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp)
target_link_libraries(runTests FancyLib ${GTEST_LIBRARIES} pthread)

#add_dependencies(check runTests)

add_custom_target(run_tests runTests
    # run second command
    #COMMAND runTests
    )


# automatically run test at the end of make
#add_custom_command(TARGET runTests
#                       POST_BUILD
#                       COMMAND runTests
#                       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#                       COMMENT "Running runTests" VERBATIM)

