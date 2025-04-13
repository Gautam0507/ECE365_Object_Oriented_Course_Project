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
        int mazeSize = maze.getMazeSize();
        visited.resize(mazeSize, std::vector<bool>(mazeSize, false));
        curPosition = maze.getPoint(0, 0);
        visited[curPosition.getRow()][curPosition.getCol()] = true;
    };
    Point getCurPosition() const { return curPosition; }
    void makeNextMove();
    bool checkDestination() const;
    bool checkPathEnd() const;
    void printMazeAndPath() const;
    void saveMazeAndPath(const std::string& mazeFileName = "maze.txt",
                         const std::string& pathFileName = "path.txt");

   private:
    Maze maze;
    Path path;
    std::vector<std::vector<bool>> visited;
    Point curPosition;
    int curPathIdx = 0;
    void markVisited(const Point& point);
    bool checkVisited(const Point& point) const;
    bool checkBounds(int newRow, int newCol) const;
};
