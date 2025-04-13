# ECE365_Object_Oriented_Course_Project

This project implements a maze path validation system that checks whether a given path can successfully navigate from the starting point to the destination in a grid-based maze.

## Overview

The maze path validation system consists of several core components:

- **Point**: Represents a single cell in the maze grid with a position and type (path or obstacle)
- **Maze**: Represents the complete grid-based maze loaded from a file
- **Path**: Represents a sequence of directional moves (up, down, left, right, stop)
- **PathTraversal**: Manages traversing a path through a maze and validating the path

## File Format

### Maze File
- Contains binary values (0 for obstacles, 1 for traversable paths)
- The number of values must form a perfect square
- The starting position (0,0) must be a path (value 1)

### Path File
- Contains a sequence of directional values:
  - 0: Stop
  - 1: Up
  - 2: Right
  - 3: Down
  - 4: Left
- The path must end with a stop direction (0)

### Syntax for both files 
- Values must be comma-separated or whitespace-separated
- Lines starting with '#' are treated as comments and ignored
- No other special characters should be used, as they will cause parsing errors

# Installation and Build Instructions

## Option 1: Compiling with g++

To compile the project directly using g++:

```bash
# Compile all source files with include path
g++ -std=c++11 -o Maze_solver src/*.cpp -Iinclude
```

```bash
# Run the program with maze and path files
./Maze_solver <maze_file> <path_file>
```

```bash
# Example usage with sample files
./Maze_solver maze.txt path.txt
```

## Option 2: Building with CMake

```bash
# Generate build system
cmake -S . -B build
```
```bash
# Build the project
cmake --build build
```
```bash
# Run the program
./build/src/Maze_solver <maze_file> <path_file>
```
```bash
# Example usage with sample files
./build/src/Maze_solver maze.txt path.txt
```

# Project Testing Guide

After installing the project, you can test the code in two main ways:

## Testing with Sample Files

To test with the sample maze and path files in the root directory:

```bash
# Using the compiled executable directly if compiled using cmake 
./build/src/Maze_solver maze.txt path.txt
```

```bash
# Using the compiled executable directly if compiled using cmake 
./Maze_solver maze.txt path.txt
```

The program will validate whether the path successfully navigates through the maze, printing the results to the console.

## Running All Tests

The project includes a comprehensive test suite in the `tests` directory. You can run all tests automatically:

```bash
# Make the script executable if needed
chmod +x run.sh

# Run all tests
./run.sh
```

This will:
- Run 16 test cases covering various scenarios
- Display pass/fail status for each test
- Store detailed results in `maze_solver_results.log`

The test cases cover error handling, path validation, and various edge cases like:
- File not found errors
- Invalid maze formats
- Path validation failures
- Boundary violations
- Revisiting cells
