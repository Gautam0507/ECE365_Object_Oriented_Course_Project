enable_testing()

add_executable(tests path_test.cpp)
target_link_libraries(tests PRIVATE Maze_solver_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
