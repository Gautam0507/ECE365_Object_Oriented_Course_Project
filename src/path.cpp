#include "path.hpp"

#include <fstream>
#include <iostream>
#include <string>

Path::Path(const std::string &filename) { bool isParsed = parseFile(filename); }

Path::~Path() {}

bool Path::parseFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    // Clear existing path if present
    path.clear();

    std::string line;
    while (std::getline(file, line)) {
        for (char ch : line) {
            if (ch == '#') {
                break;
            }
            if (ch >= '0' && ch <= '4') {
                path.push_back(ch - '0');
            }
        }
    }

    if (path.empty()) {
        std::cerr << "Error: file " << filename
                  << " does not contain any valid numbers (0 - 4)" << std::endl;
        return false;
    }
    return true;
}
