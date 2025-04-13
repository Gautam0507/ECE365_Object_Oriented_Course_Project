#include "path_traversal.hpp"

#include <iostream>
#include <utility>

#include "point.hpp"

bool PathTraversal::checkVisited(const Point& point) const
{
    return visited[point.getRow()][point.getCol()];
}

void PathTraversal::markVisited(const Point& point)
{
    // check is done right before calling the function
    visited[point.getRow()][point.getCol()] = true;
}

bool PathTraversal::checkBounds(int newRow, int newCol) const
{
    if (newRow < 0 || newRow > maze.getMazeSize() - 1 || newCol < 0 ||
        newCol > maze.getMazeSize() - 1) {
        std::cerr << "Error: Position [" << newRow << "," << newCol
                  << "] is out of bounds. Maze size is " << maze.getMazeSize()
                  << "x" << maze.getMazeSize() << std::endl;
        return false;
    }
    return true;
}

void PathTraversal::makeNextMove()
{
    if (checkDestination()) {
        throw std::logic_error(
            "Path continues after reaching the destination at position [" +
            std::to_string(curPosition.getRow()) + "," +
            std::to_string(curPosition.getCol()) + "]");
    }

    std::pair<int, int> move;
    try {
        move = path.getMove(curPathIdx);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to get move at path index " +
                                 std::to_string(curPathIdx) + ": " + e.what());
    }

    int newRow = curPosition.getRow() + move.first;
    int newCol = curPosition.getCol() + move.second;

    bool isWithinBounds = checkBounds(newRow, newCol);
    if (!isWithinBounds) {
        throw std::out_of_range(
            "Move from [" + std::to_string(curPosition.getRow()) + "," +
            std::to_string(curPosition.getCol()) + "] to [" +
            std::to_string(newRow) + "," + std::to_string(newCol) +
            "] is out of maze bounds");
    }

    Point nextPoint;
    try {
        nextPoint = maze.getPoint(newRow, newCol);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to get maze point at [" +
                                 std::to_string(newRow) + "," +
                                 std::to_string(newCol) + "]: " + e.what());
    }

    bool isPath = nextPoint.isPath();
    if (!isPath) {
        throw std::invalid_argument(
            "Move to position [" + std::to_string(newRow) + "," +
            std::to_string(newCol) + "] places the position in a no-path cell");
    }

    bool isVisited = checkVisited(nextPoint);
    if (isVisited) {
        throw std::invalid_argument(
            "Move to position [" + std::to_string(newRow) + "," +
            std::to_string(newCol) +
            "] places the position in a previously visited cell");
    }

    markVisited(nextPoint);
    curPosition = nextPoint;
    if (!checkPathEnd()) {
        ++curPathIdx;
    }
}

bool PathTraversal::checkDestination() const
{
    return curPosition ==
           maze.getPoint(maze.getMazeSize() - 1, maze.getMazeSize() - 1);
}

bool PathTraversal::checkPathEnd() const
{
    if (curPathIdx == path.getSize() - 1) {
        return true;
    }
    if (path.getMove(curPathIdx) == std::make_pair(0, 0)) {
        return true;
    }
    return false;
}

void PathTraversal::printMazeAndPath() const
{
    std::cout << maze;
    std::cout << path;
}

void PathTraversal::saveMazeAndPath(const std::string& mazeFileName,
                                    const std::string& pathFileName)
{
    bool mazeSaved = maze.saveToFile(mazeFileName);
    bool pathSaved = path.saveToFile(pathFileName);

    std::cout << std::endl;
    if (mazeSaved) {
        std::cout << "Maze saved to " << mazeFileName << std::endl;
    } else {
        std::cerr << "Failed to save maze to " << mazeFileName << std::endl;
    }

    if (pathSaved) {
        std::cout << "Path saved to " << pathFileName << std::endl;
    } else {
        std::cerr << "Failed to save path to " << pathFileName << std::endl;
    }
}
