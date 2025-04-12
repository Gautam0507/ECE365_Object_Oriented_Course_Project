#include <iostream>
#include <string>

#include "path_traversal.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <maze_file> <path_file>"
                  << std::endl;
        return 1;
    }

    try {
        PathTraversal pathTraversal(argv[1], argv[2]);
        pathTraversal.printMazeAndPath();

        // Follow the path until completion or failure
        while (!pathTraversal.checkDestination() &&
               !pathTraversal.checkPathEnd()) {
            pathTraversal.makeNextMove();
        }

        // Report result
        bool success = pathTraversal.checkDestination();
        if (success) {
            std::cout << "Destination reached!" << std::endl;
        } else {
            std::cerr << "Path ended without reaching the destination."
                      << std::endl;
        }

        pathTraversal.saveMazeAndPath();

        return success ? 0 : 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
