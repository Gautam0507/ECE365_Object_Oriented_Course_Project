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
    if (newRow < 0 || newRow > maze.getSize() - 1 || newCol < 0 ||
        newCol > maze.getSize() - 1) {
        std::cerr << "Error: Out of bounds" << std::endl;
        return false;
    }
    return true;
}

void PathTraversal::makeNextMove()
{
    std::pair<int, int> move = path.getMove(curPathidx);
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
        ++curPathidx;
    }
}

bool PathTraversal::checkDestination() const
{
    return curPosition == maze.getPoint(maze.getSize() - 1, maze.getSize() - 1);
}

bool PathTraversal::checkPathEnd() const
{
    if (curPathidx == path.getSize() - 1) {
        return true;
    }
    if (path.getMove(curPathidx) == std::make_pair(0, 0)) {
        return true;
    }
    return false;
}
