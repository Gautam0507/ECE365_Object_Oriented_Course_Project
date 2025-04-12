#include "maze.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

Maze::Maze(const std::string& filename)
{
    bool isLoaded = loadMazeFromFile(filename);
    if (!isLoaded) {
        throw std::runtime_error("Could not load maze from file");
    }
}

bool Maze::loadMazeFromFile(const std::string& filename)
{
    std::vector<int> mazeTemp;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }
    // Loading data into a 1D vector
    maze.clear();

    std::string line;
    while (std::getline(file, line)) {
        for (char ch : line) {
            if (ch == '#') {
                break;
            }
            if (ch == '0' || ch == '1') {
                mazeTemp.push_back(static_cast<int>(ch - '0'));
            }
        }
    }

    if (mazeTemp.empty()) {
        std::cerr << "Error: file " << filename
                  << " does not contain any valid numbers (0 - 1)" << std::endl;
        return false;
    }

    if (mazeTemp.at(0) != 1) {
        std::cerr << "Error: Maze entrance is not a path block" << std::endl;
        return false;
    }

    // Checking if the number of values is a perfect square
    mazeSize = findSquareRoot(mazeTemp.size());
    if (mazeSize == -1) {
        std::cerr << "Error: the number of values " << std::to_string(mazeSize)
                  << " in the file is not a perfect square: " << std::endl;
        return false;
    } else {
        assignMaze(mazeTemp);
    }
    return true;
}

int Maze::findSquareRoot(int n) const
{
    int root = static_cast<int>(std::sqrt(n));
    return (root * root == n) ? root : -1;
}

void Maze::assignMaze(const std::vector<int>& maze1)
{
    maze.resize(mazeSize);
    for (int row = 0; row < mazeSize; ++row) {
        maze[row].resize(mazeSize);
        for (int col = 0; col < mazeSize; ++col) {
            maze[row][col].setPoint(row, col, maze1[row * mazeSize + col]);
        }
    }
}

bool Maze::saveMazeToFile(const std::string& filename)
{
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    for (int row = 0; row < mazeSize; ++row) {
        for (int col = 0; col < mazeSize; ++col) {
            auto val = maze[row][col].getValue();
            outfile << static_cast<int>(val);
            if (col != mazeSize - 1) {
                outfile << ",";
            }
        }
        outfile << std::endl;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Maze& maze)
{
    const std::vector<std::vector<Point>>& mazeData = maze.getMaze();
    int mazeSize = maze.getSize();

    os << std::endl;
    os << "The given maze is: " << std::endl;
    for (int row = 0; row < mazeSize; ++row) {
        for (int col = 0; col < mazeSize; ++col) {
            os << mazeData[row][col];
            if (col != mazeSize - 1) {
                os << ",";
            }
        }
        os << std::endl;
    }
    return os;
}
