#include <iostream>
#include <stdexcept>
#include <string>

#include "maze.hpp"
#include "path_traversal.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <maze_file> <path_file>"
                  << std::endl;
        return 1;
    }
    std::string mazeFileName = argv[1];
    std::string pathFileName = argv[2];

    PathTraversal pathTraversal(mazeFileName, pathFileName);
    while (!pathTraversal.checkDestination() || !pathTraversal.checkPathEnd()) {
        try {
            pathTraversal.makeNextMove();
        } catch (const std::runtime_error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }

    if (pathTraversal.checkDestination()) {
        std::cout << "Destination reached!" << std::endl;
        return 0;
    } else {
        std::cerr << "Error: Path end reached without reaching the destination "
                  << std::endl;
        return -1;
    }
}
