#include "path.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

Path::Path(const std::string& filename)
{
    bool isLoaded = loadFromFile(filename);
    bool isValidPath = validate();
    if (!isLoaded || !isValidPath) {
        throw std::runtime_error("Could not load path from file");
    }
}

bool Path::loadFromFile(const std::string& filename)
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
                int value = ch - '0';
                path.push_back(static_cast<Direction>(value));
            } else if (ch == ',' || std::isspace(ch)) {
                // Valid separator, ignore
                continue;
            } else {
                // Invalid character found
                std::cerr << "Error: invalid character '" << ch
                          << "' in path file" << std::endl;
                return false;
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

bool Path::validate() const
{
    bool stopFound = false;
    for (Direction dir : path) {
        int value = static_cast<int>(dir);
        if (value < 0 || value > 4) {
            std::cerr << "Error: path contains invalid value " << value
                      << std::endl;
            return false;
        }
        if (dir == Direction::Stop) {
            stopFound = true;
        }
        if (stopFound && dir != Direction::Stop) {
            std::cerr << "Error: path contains value " << static_cast<int>(dir)
                      << " after a zero value" << std::endl;
            return false;
        }
    }
    return true;
}

std::vector<std::string> Path::pathToString() const
{
    std::vector<std::string> pathString;
    for (Direction dir : path) {
        switch (dir) {
            case Direction::Up:
                pathString.push_back("Up");
                break;
            case Direction::Right:
                pathString.push_back("Right");
                break;
            case Direction::Down:
                pathString.push_back("Down");
                break;
            case Direction::Left:
                pathString.push_back("Left");
                break;
            case Direction::Stop:
                break;
            default:
                pathString.push_back("Invalid value:" +
                                     std::to_string(static_cast<int>(dir)));
        }
    }
    return pathString;
}

std::pair<int, int> Path::getMove(int idx) const
{
    switch (path[idx]) {
        case Direction::Up:
            return std::make_pair(-1, 0);
        case Direction::Right:
            return std::make_pair(0, 1);
        case Direction::Down:
            return std::make_pair(1, 0);
        case Direction::Left:
            return std::make_pair(0, -1);
        case Direction::Stop:
            return std::make_pair(0, 0);
        default:
            throw std::runtime_error(
                "Invalid direction" +
                std::to_string(static_cast<int>(path[idx])));
            return std::make_pair(-1, -1);
    }
}

bool Path::saveToFile(const std::string& filename)
{
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        outfile << static_cast<int>(path[i]);
        if (i != path.size() - 1) {
            outfile << ",";
        }
    }
    outfile.close();
    return true;
}

std::ostream& operator<<(std::ostream& os, const Path& path)
{
    std::vector<std::string> pathString = path.pathToString();

    os << std::endl << "The path to be taken by the user: " << std::endl;
    for (int i = 0; i < pathString.size(); ++i) {
        os << "Move " << std::to_string(i) << ": " << pathString[i]
           << std::endl;
    }
    os << std::endl;
    return os;
}
