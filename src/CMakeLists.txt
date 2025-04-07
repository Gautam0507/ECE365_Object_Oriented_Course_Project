# Main program files
set(SOURCE_FILES maze.cpp path.cpp path_traversal.cpp point.cpp)

# Create a library with all source files EXCEPT main.cpp
add_library(Maze_solver_lib ${SOURCE_FILES})
target_include_directories(Maze_solver_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Create the main executable with main.cpp
add_executable(Maze_solver main.cpp)
target_link_libraries(Maze_solver PRIVATE Maze_solver_lib)
target_include_directories(Maze_solver PRIVATE ${CMAKE_SOURCE_DIR}/include)
