enable_testing()

# ====== UNIT TESTS (Component Level) ======
set(UNIT_TEST_SOURCES
    basic_test.cpp
    # Add other unit test files here
)

add_executable(maze_unit_tests ${UNIT_TEST_SOURCES})
target_link_libraries(maze_unit_tests PRIVATE 
    Maze_solver_lib 
    GTest::gtest_main
)
target_include_directories(maze_unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Register unit tests with CTest
include(GoogleTest)
gtest_discover_tests(maze_unit_tests)

# # ====== INTEGRATION TESTS (Full Program) ======
# # Define test input files (put real maze and path files here)
# set(TEST_MAZE_FILES
#     "${CMAKE_SOURCE_DIR}/test_data/maze1.txt"
#     "${CMAKE_SOURCE_DIR}/test_data/maze2.txt"
# )
# set(TEST_PATH_FILES
#     "${CMAKE_SOURCE_DIR}/test_data/path1.txt"
#     "${CMAKE_SOURCE_DIR}/test_data/path2.txt"
# )

# # Create a test for each combination
# set(test_index 0)
# foreach(maze_file ${TEST_MAZE_FILES})
#     foreach(path_file ${TEST_PATH_FILES})
#         # Extract just the filenames for test naming
#         get_filename_component(maze_name ${maze_file} NAME_WE)
#         get_filename_component(path_name ${path_file} NAME_WE)
        
#         # Add a test that runs the main executable with these files
#         add_test(
#             NAME integration_${maze_name}_${path_name}
#             COMMAND $<TARGET_FILE:Maze_solver> ${maze_file} ${path_file}
#             WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#         )
        
#         # Optional: Set a timeout to prevent hanging tests
#         set_tests_properties(integration_${maze_name}_${path_name} PROPERTIES
#             TIMEOUT 30  # 30 seconds timeout
#         )
        
#         math(EXPR test_index "${test_index} + 1")
#     endforeach()
# endforeach()
