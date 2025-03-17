#include "maze.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

Maze::Maze(const std::string& filename)
{
    bool isLoaded = loadFromFile(filename);
}

bool Maze::loadFromFile(const std::string& filename)
{
    std::vector<int> maze1d;
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
                maze1d.push_back(static_cast<int>(ch - '0'));
            }
        }
    }

    if (maze1d.empty()) {
        std::cerr << "Error: file " << filename
                  << " does not contain any valid numbers (0 - 1)" << std::endl;
        return false;
    }

    // Checking if the number of values is a perfect square
    int n = findSquareRoot(maze1d.size());
    if (n == -1) {
        std::cerr << "Error: the number of values " << std::to_string(n)
                  << " in the file is not a perfect square: " << std::endl;
        return false;
    } else {
        reshapeMaze(maze1d, n);
    }
    return true;
}

int Maze::findSquareRoot(int n) const
{
    int root = static_cast<int>(std::sqrt(n));
    return (root * root == n) ? root : -1;
}

void Maze::reshapeMaze(const std::vector<int>& maze1d, int n)
{
    maze.resize(n);
    for (int i = 0; i < n; ++i) {
        maze[i].resize(n);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            maze[i][j].setValue(maze1d[i * n + j]);
        }
    }
}

void Maze::printMaze() const
{
    std::cout << std::endl;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            printCell(maze[i][j].getValue());
        }
        std::cout << std::endl;
    }
}

void Maze::printCell(int i) const
{
    // 1 denotes path and 0 denotes no path
    if (i == 1) {
        std::cout << "[ ]";
    } else if (i == 0) {
        std::cout << "[#]";
    } else {
        std::cerr << "Error: invalid value in the maze" << std::endl;
    }
}

bool Maze::saveMazeToFile(const std::string& filename)
{
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return false;
    }

    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            outfile << maze[i][j].getValue();
            if (j != maze[i].size() - 1) {
                outfile << ",";
            }
        }
        outfile << std::endl;
    }
    return true;
}
