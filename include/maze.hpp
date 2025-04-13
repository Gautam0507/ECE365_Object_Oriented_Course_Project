/**
 * @file maze.hpp
 * @brief Defines the Maze class representing a grid-based maze
 */
#pragma once

#include <string>
#include <vector>

#include "point.hpp"

/**
 * @class Maze
 * @brief Represents a square grid-based maze
 *
 * A Maze consists of a grid of Point objects, where each Point
 * can be either a traversable path or an obstacle. The maze is
 * loaded from a file containing binary values (0 for obstacle, 1 for path).
 */
class Maze
{
   public:
    /**
     * @brief Constructs a Maze from a file
     * @param filename Name of the file containing maze data
     * @throws std::runtime_error if the maze cannot be loaded
     */
    Maze(const std::string& filename);

    /**
     * @brief Loads a maze from a file
     * @param filename Name of the file to load from
     * @return true if loaded successfully, false otherwise
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Saves the maze to a file
     * @param filename Name of the file to save to
     * @return true if saved successfully, false otherwise
     */
    bool saveToFile(const std::string& filename);

    /**
     * @brief Gets the size of the maze (width/height)
     * @return Size of the maze (number of rows/columns)
     */
    int getMazeSize() const { return mazeSize; }

    /**
     * @brief Gets a specific point in the maze
     * @param row Row index
     * @param col Column index
     * @return The Point at the specified location
     * @throws std::out_of_range if coordinates are invalid
     */
    Point getPoint(int row, int col) const;

    /**
     * @brief Gets the entire maze grid
     * @return Reference to the 2D vector of Points representing the maze
     */
    const std::vector<std::vector<Point>>& getMaze() const { return maze; }

   private:
    int mazeSize = 0;  ///< Dimension of the maze (width/height)
    std::vector<std::vector<Point>>
        maze;  ///< 2D grid of points representing the maze

    /**
     * @brief Finds if a number is a perfect square
     * @param n Number to check
     * @return Square root if n is a perfect square, -1 otherwise
     */
    int findSquareRoot(const int n) const;

    /**
     * @brief Creates the maze grid from a flat vector of values
     * @param mazeData Vector of binary values (0/1) representing maze cells
     */
    void populateMazeGrid(const std::vector<int>& mazeData);
};

/**
 * @brief Stream insertion operator for Maze objects
 * @param os Output stream
 * @param maze Maze to output
 * @return Modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Maze& maze);
