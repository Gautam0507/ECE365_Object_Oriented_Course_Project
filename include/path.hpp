#pragma once
#include <string>
#include <utility>
#include <vector>

class Path
{
   public:
    Path(const std::string &filename);
    void printPath() const;
    void savePathToFile(const std::string &filename);
    bool loadPathFromFile(const std::string &filename);
    std::pair<int, int> getMove(int idx) const;
    int getSize() const { return path.size(); }

   private:
    std::vector<int> path;
    bool validatePath() const;
    std::vector<std::string> pathToString() const;
};
