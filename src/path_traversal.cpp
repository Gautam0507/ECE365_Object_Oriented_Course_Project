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
    visited[point.getRow()][point.getCol()] = true;
}

bool PathTraversal::checkBounds(int newRow, int newCol) const
{
    if (newRow < 0 || newRow > maze.getMazeSize() - 1 || newCol < 0 ||
        newCol > maze.getMazeSize() - 1) {
        std::cerr << "Error: Out of bounds" << std::endl;
        return false;
    }
    return true;
}

void PathTraversal::makeNextMove()
{
    std::pair<int, int> move = path.getMove(curPathIdx);
    if (move.first == -1 && move.second == -1) {
        std::cerr << "Error: Invalid move" << std::endl;
        return;
    }

    int newRow = curPosition.getRow() + move.first;
    int newCol = curPosition.getCol() + move.second;

    bool isWithinBounds = checkBounds(newRow, newCol);
    if (!isWithinBounds) {
        std::cerr << "Error: Out of bounds" << std::endl;
        std::cerr << "Current position: " << newRow << ", " << newCol
                  << std::endl;
        throw std::runtime_error("Error: Out of bounds");

        return;
    }

    Point nextPoint = maze.getPoint(newRow, newCol);

    bool isPath = nextPoint.isPath();
    if (!isPath) {
        std::cout << "Error: The move places the position in a no path cell"
                  << std::endl;
        throw std::runtime_error(
            "Error: The move places the position in a no path cell");
        return;
    }

    bool isVisited = checkVisited(nextPoint);
    if (isVisited) {
        std::cout << "Error: The move places the position in a visited cell"
                  << std::endl;
        throw std::runtime_error(
            "Error: The move places the position in a visited cell");
        return;
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
