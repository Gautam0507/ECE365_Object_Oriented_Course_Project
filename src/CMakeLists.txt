set(SOURCE_FILES main.cpp maze.cpp path.cpp path_traversal.cpp point.cpp)

add_library(Maze_solver_lib ${SOURCE_FILES})
add_executable(Maze_solver main.cpp)

target_link_libraries(Maze_solver PRIVATE Maze_solver_lib)
target_include_directories(Maze_solver PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(Maze_solver_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)
