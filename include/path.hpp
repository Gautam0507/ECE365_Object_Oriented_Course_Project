#pragma once
#include <string>
#include <vector>

class Path
{
   public:
    Path(const std::string &filename);
    Path(Path &&) = default;
    Path(const Path &) = default;
    ~Path();
    void printPath() const;
    void savePathToFile(const std::string &filename);

   private:
    std::vector<int> path;
    bool parseFile(const std::string &filename);
    bool validatePath() const;
    std::vector<std::string> pathToString() const;
};
