# ECE365_Object_Oriented_Course_Project


Compile this using Visual studio in windows (should recognize cmake automatically)

If you  have cmake run the following  commands from the root folder 

```bash 
cmake -S . -B build 
cmake --build build 

./build/src/Maze_solver <maze_file> <path_file>
```
In the above commands replace <maze_file> with the path to the maze file and similarly for the path file.

Note given testcases are inside the `./tests/TestCases/test/` folder. 

The bat files inside each of the folders in testcases might work on windows. 

The `run_given_tests.sh` file does not work on winoows unless you have a bash compatible shell installed. 
