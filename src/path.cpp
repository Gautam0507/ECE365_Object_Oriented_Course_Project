#include "path.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

Path::Path(const std::string &filename)
{
    bool isLoaded = loadPathFromFile(filename);
    bool isValidPath = validatePath();
    if (!isLoaded || !isValidPath) {
        throw std::runtime_error("could not load path from file");
    }
}

bool Path::loadPathFromFile(const std::string &filename)
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

bool Path::validatePath() const
{
    bool zeroFound = false;
    for (int value : path) {
        if (value < 0 || value > 4) {
            std::cerr << "Error: path contains invalid value " << value
                      << std::endl;
            return false;
        }
        if (value == 0) {
            zeroFound = true;
        }
        if (zeroFound && value != 0) {
            std::cerr << "Error: path contains value " << value
                      << " after a zero value" << std::endl;
            return false;
        }
    }
    return true;
}

std::vector<std::string> Path::pathToString() const
{
    std::vector<std::string> pathString;
    for (int value : path) {
        switch (value) {
            case 1:
                pathString.push_back("Up");
                break;
            case 2:
                pathString.push_back("Right");
                break;
            case 3:
                pathString.push_back("Down");
                break;
            case 4:
                pathString.push_back("Left");
                break;
            case 0:
                break;
            default:
                pathString.push_back("Invalid value:" + std::to_string(value));
        }
    }
    return pathString;
}

void Path::printPath() const
{
    std::vector<std::string> pathString = pathToString();
    std::cout << "The path to be taken by the user: " << std::endl;
    for (int i = 0; i < pathString.size(); ++i) {
        std::cout << "Move " << std::to_string(i) << ": " << pathString[i]
                  << std::endl;
    }
}

std::pair<int, int> Path::getMove(int idx) const
{
    switch (path[idx]) {
        case 1:
            return std::make_pair(-1, 0);
        case 2:
            return std::make_pair(0, 1);
        case 3:
            return std::make_pair(1, 0);
        case 4:
            return std::make_pair(0, -1);
        case 0:
            return std::make_pair(0, 0);
        default:
            std::cerr << "Got an invalid direction" << std::endl;
            return std::make_pair(-1, -1);
    }
}

void Path::savePathToFile(const std::string &filename)
{
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cout << "The output file cannot be created";
        return;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        outfile << path[i];
        if (i != path.size() - 1) {
            outfile << ",";
        }
    }
    outfile.close();
}
