#pragma once

#include <string>
#include <vector>

#include "point.hpp"

class Maze
{
   public:
    Maze(const std::string& filename);
    bool loadMazeFromFile(const std::string& filename);
    bool saveMazeToFile(const std::string& filename);
    int getSize() const { return mazeSize; }
    Point getPoint(int row, int col) const { return maze.at(row).at(col); }
    const std::vector<std::vector<Point>>& getMaze() const { return maze; }

   private:
    int mazeSize = 0;
    std::vector<std::vector<Point>> maze;
    int findSquareRoot(const int n) const;
    void assignMaze(const std::vector<int>& maze1d);
};
std::ostream& operator<<(std::ostream& os, const Maze& maze);
