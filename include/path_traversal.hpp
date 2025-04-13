/**
 * @file path_traversal.hpp
 * @brief Defines the PathTraversal class for navigating through a maze using a
 * path
 */
#pragma once

#include <string>
#include <vector>

#include "maze.hpp"
#include "path.hpp"
#include "point.hpp"

/**
 * @class PathTraversal
 * @brief Manages traversing a path through a maze and validates the path
 *
 * PathTraversal combines a Maze and a Path to simulate and validate
 * movement through the maze according to the path. It tracks the current
 * position and which cells have been visited, ensuring the path is valid.
 */
class PathTraversal
{
   public:
    /**
     * @brief Constructs a PathTraversal with a maze and path from files
     * @param mazeFileName Name of the file containing maze data
     * @param pathFileName Name of the file containing path data
     *
     * Initializes a traversal starting at position (0,0) in the maze
     * and marks it as visited.
     */
    PathTraversal(const std::string& mazeFileName,
                  const std::string& pathFileName)
        : maze(mazeFileName), path(pathFileName)
    {
        int mazeSize = maze.getMazeSize();
        visited.resize(mazeSize, std::vector<bool>(mazeSize, false));
        curPosition = maze.getPoint(0, 0);
        visited[curPosition.getRow()][curPosition.getCol()] = true;
    };

    /**
     * @brief Gets the current position in the maze
     * @return Point representing current position
     */
    Point getCurPosition() const { return curPosition; }

    /**
     * @brief Checks if a point has been visited during traversal
     * @param point Point to check
     * @return true if the point has been visited, false otherwise
     */
    bool checkVisited(const Point& point) const;

    /**
     * @brief Executes the next move in the path
     * @throws std::runtime_error if move retrieval fails
     * @throws std::out_of_range if move is outside maze bounds
     * @throws std::invalid_argument if move leads to an obstacle or revisits a
     * cell
     * @throws std::logic_error if the path continues after reaching destination
     */
    void makeNextMove();

    /**
     * @brief Checks if coordinates are within maze boundaries
     * @param newRow Row position to check
     * @param newCol Column position to check
     * @return true if coordinates are valid, false otherwise
     */
    bool checkBounds(int newRow, int newCol) const;

    /**
     * @brief Checks if current position is the maze destination
     * @return true if at bottom-right corner of maze, false otherwise
     */
    bool checkDestination() const;

    /**
     * @brief Checks if the path has been fully traversed
     * @return true if at the path's end, false otherwise
     */
    bool checkPathEnd() const;

    /**
     * @brief Prints the maze grid and path details to standard output
     */
    void printMazeAndPath() const;

    /**
     * @brief Saves the current maze and path to files
     * @param mazeFileName Name of the file to save maze data to (default:
     * "maze.txt")
     * @param pathFileName Name of the file to save path data to (default:
     * "path.txt")
     */
    void saveMazeAndPath(const std::string& mazeFileName = "maze.txt",
                         const std::string& pathFileName = "path.txt");

   private:
    Maze maze;  ///< Maze being traversed
    Path path;  ///< Path being followed
    std::vector<std::vector<bool>>
        visited;         ///< Tracks which cells have been visited
    Point curPosition;   ///< Current position in the maze
    int curPathIdx = 0;  ///< Current index in the path

    /**
     * @brief Marks a point as visited
     * @param point Point to mark as visited
     */
    void markVisited(const Point& point);
};
