#include <string>
#include <vector>

#include "point.hpp"

class Maze
{
   public:
    Maze(const std::string& filename);
    void printMaze() const;
    bool loadFromFile(const std::string& filename);
    bool saveMazeToFile(const std::string& filename);

   private:
    int size = 0;
    std::vector<std::vector<Point>> maze;
    int findSquareRoot(const int n) const;
    void reshapeMaze(const std::vector<int>& maze1d, int n);
    void printCell(int i) const;
};
