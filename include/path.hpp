/**
 * @file path.hpp
 * @brief Defines the Path class representing a sequence of movements through a
 * maze
 */
#pragma once
#include <string>
#include <utility>
#include <vector>

/**
 * @class Path
 * @brief Represents a sequence of movements through a maze
 *
 * A Path consists of a series of directions (up, down, left, right, stop)
 * that define how to move through a maze from a starting point.
 */
class Path
{
   public:
    /**
     * @enum Direction
     * @brief Defines possible movement directions in a maze
     */
    enum class Direction
    {
        Stop = 0,   ///< No movement
        Up = 1,     ///< Move up (decrease row)
        Right = 2,  ///< Move right (increase column)
        Down = 3,   ///< Move down (increase row)
        Left = 4    ///< Move left (decrease column)
    };

    /**
     * @brief Constructs a Path from a file
     * @param filename Name of the file containing path data
     * @throws std::runtime_error if the path cannot be loaded or is invalid
     */
    Path(const std::string& filename);

    /**
     * @brief Saves the path to a file
     * @param filename Name of the file to save to
     * @return true if saved successfully, false otherwise
     */
    bool saveToFile(const std::string& filename);

    /**
     * @brief Loads a path from a file
     * @param filename Name of the file to load from
     * @return true if loaded successfully, false otherwise
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Gets the row/column changes for a specific move
     * @param idx Index of the move in the path
     * @return Pair of (row_change, column_change) representing the move
     * @throws std::out_of_range if idx is invalid
     * @throws std::logic_error if direction value is invalid
     */
    std::pair<int, int> getMove(int idx) const;

    /**
     * @brief Gets the number of moves in the path
     * @return Size of the path
     */
    int getSize() const { return path.size(); }

    /**
     * @brief Converts the path to a vector of string descriptions
     * @return Vector of direction names (Up, Right, Down, Left)
     */
    std::vector<std::string> pathToString() const;

   private:
    std::vector<Direction> path;  ///< Sequence of directions

    /**
     * @brief Validates the path for correctness
     * @return true if path is valid, false otherwise
     */
    bool validate() const;
};

/**
 * @brief Stream insertion operator for Path objects
 * @param os Output stream
 * @param path Path to output
 * @return Modified output stream
 */
std::ostream& operator<<(std::ostream& os, const Path& path);
