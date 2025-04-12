#pragma once
#include <string>
#include <utility>
#include <vector>

class Path
{
   public:
    Path(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    std::pair<int, int> getMove(int idx) const;
    int getSize() const { return path.size(); }
    std::vector<std::string> pathToString() const;

   private:
    std::vector<int> path;
    bool validate() const;
};

std::ostream& operator<<(std::ostream& os, const Path& path);
