#pragma once
#include <string>
#include <vector>

class Path
{
   public:
    Path(const std::string &filename);
    ~Path();

   private:
    std::vector<int> path;
    bool parseFile(const std::string &filename);
};
