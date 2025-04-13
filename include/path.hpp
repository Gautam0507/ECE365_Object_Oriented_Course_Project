#pragma once
#include <string>
#include <utility>
#include <vector>

class Path
{
   public:
    enum class Direction
    {
        Stop = 0,
        Up = 1,
        Right = 2,
        Down = 3,
        Left = 4
    };

    Path(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    std::pair<int, int> getMove(int idx) const;
    int getSize() const { return path.size(); }

   private:
    std::vector<Direction> path;
    std::vector<std::string> pathToString() const;
    bool validate() const;
};

std::ostream& operator<<(std::ostream& os, const Path& path);
