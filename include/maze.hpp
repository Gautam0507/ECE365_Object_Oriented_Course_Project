#pragma once

#include <string>
#include <vector>

#include "point.hpp"

class Maze
{
   public:
    Maze(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    int getMazeSize() const { return mazeSize; }
    Point getPoint(int row, int col) const;
    const std::vector<std::vector<Point>>& getMaze() const { return maze; }

   private:
    int mazeSize = 0;
    std::vector<std::vector<Point>> maze;
    int findSquareRoot(const int n) const;
    void populateMazeGrid(const std::vector<int>& mazeData);
};
std::ostream& operator<<(std::ostream& os, const Maze& maze);
