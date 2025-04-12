#pragma once

#include <string>
#include <vector>

#include "maze.hpp"
#include "path.hpp"
#include "point.hpp"

class PathTraversal
{
   public:
    PathTraversal(const std::string& mazeFileName,
                  const std::string& pathFileName)
        : maze(mazeFileName), path(pathFileName)
    {
        int size = maze.getSize();
        visited.resize(size, std::vector<bool>(size, false));
        curPosition = maze.getPoint(0, 0);
        visited[curPosition.getRow()][curPosition.getCol()] = true;
    };
    Point getCurPosition() const { return curPosition; }

    bool checkVisited(const Point& point) const;
    void markVisited(const Point& point);
    void makeNextMove();
    bool checkBounds(int newRow, int newCol) const;
    bool checkDestination() const;
    bool checkPathEnd() const;
    void printMazeAndPath() const;
    bool saveMazeAndPath(const std::string& mazeFileName = "maze.txt",
                         const std::string& pathFileName = "path.txt");

   private:
    Path path;
    Maze maze;
    std::vector<std::vector<bool>> visited;
    Point curPosition;
    int curPathidx = 0;
};
