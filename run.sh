#!/bin/sh

# Possible executable paths
CMAKE_EXECUTABLE="./build/src/Maze_solver"
DIRECT_EXECUTABLE="./Maze_solver"

# Choose executable based on availability
if [ -f "$CMAKE_EXECUTABLE" ]; then
    EXECUTABLE="$CMAKE_EXECUTABLE"
    echo "Using CMake build executable: $EXECUTABLE"
elif [ -f "$DIRECT_EXECUTABLE" ]; then
    EXECUTABLE="$DIRECT_EXECUTABLE"
    echo "Using directly compiled executable: $EXECUTABLE"
else
    echo "Error: No executable found. Please build the project first."
    echo "Options:"
    echo "  - CMake: cmake -S . -B build && cmake --build build"
    echo "  - Direct: g++ -std=c++11 -o Maze_solver src/*.cpp -Iinclude"
    exit 1
fi

# Directory containing test cases
TEST_DIR="./tests"

# Log file
LOG_FILE="maze_solver_results.log"

# Create or clear log file
echo "Maze Solver Test Results" > "$LOG_FILE"
echo "========================" >> "$LOG_FILE"
echo "Date: $(date)" >> "$LOG_FILE"
echo "Executable: $EXECUTABLE" >> "$LOG_FILE"
echo "" >> "$LOG_FILE"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE" | tee -a "$LOG_FILE"
    exit 1
fi

# Check if test directory exists
if [ ! -d "$TEST_DIR" ]; then
    echo "Error: Test directory not found at $TEST_DIR" | tee -a "$LOG_FILE"
    echo "Current directory: $(pwd)" | tee -a "$LOG_FILE"
    echo "Looking for alternative test directories..." | tee -a "$LOG_FILE"
    
    # Try to find the tests directory anywhere in the current directory tree
    FOUND_DIR=$(find . -type d -name "tests" -print -quit)
    
    if [ -n "$FOUND_DIR" ]; then
        TEST_DIR="${FOUND_DIR}"
        echo "Found alternative test directory: $TEST_DIR" | tee -a "$LOG_FILE"
        
        if [ ! -d "$TEST_DIR" ]; then
            echo "Error: 'tests' directory not found" | tee -a "$LOG_FILE"
            exit 1
        fi
    else
        echo "Error: Could not find tests directory" | tee -a "$LOG_FILE"
        exit 1
    fi
fi

# Count total test cases
TOTAL_TESTS=$(find "$TEST_DIR" -mindepth 1 -maxdepth 1 -type d -name "Test*" | wc -l)
echo "Running $TOTAL_TESTS test cases..." | tee -a "$LOG_FILE"
echo "" >> "$LOG_FILE"

# Special handling for Test00
TEST00_FOLDER="$TEST_DIR/Test00_FilesDontExistOrWrongFormat"
if [ -d "$TEST00_FOLDER" ]; then
    echo "Test Case 00: Test00_FilesDontExistOrWrongFormat" | tee -a "$LOG_FILE"
    echo "------------------------------" >> "$LOG_FILE"
    
    # First test command: Missing maze file
    echo "Running: $EXECUTABLE $TEST00_FOLDER/Maze2D.datNOTFOUND $TEST00_FOLDER/Path1D.dat" >> "$LOG_FILE"
    echo "Output:" >> "$LOG_FILE"
    OUTPUT=$("$EXECUTABLE" "$TEST00_FOLDER/Maze2D.datNOTFOUND" "$TEST00_FOLDER/Path1D.dat" 2>&1)
    STATUS=$?
    echo "$OUTPUT" >> "$LOG_FILE"
    echo "Exit Status: $STATUS" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
    
    # Second test command: Missing path file
    echo "Running: $EXECUTABLE $TEST00_FOLDER/Maze2D.dat $TEST00_FOLDER/Path1D.datNOTFOUND" >> "$LOG_FILE"
    echo "Output:" >> "$LOG_FILE"
    OUTPUT=$("$EXECUTABLE" "$TEST00_FOLDER/Maze2D.dat" "$TEST00_FOLDER/Path1D.datNOTFOUND" 2>&1)
    STATUS=$?
    echo "$OUTPUT" >> "$LOG_FILE"
    echo "Exit Status: $STATUS" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
    
    # Third test command: Files in reversed order
    echo "Running: $EXECUTABLE $TEST00_FOLDER/Path1D.dat $TEST00_FOLDER/Maze2D.dat" >> "$LOG_FILE"
    echo "Output:" >> "$LOG_FILE"
    OUTPUT=$("$EXECUTABLE" "$TEST00_FOLDER/Path1D.dat" "$TEST00_FOLDER/Maze2D.dat" 2>&1)
    STATUS=$?
    echo "$OUTPUT" >> "$LOG_FILE"
    echo "Exit Status: $STATUS" >> "$LOG_FILE"
    
    # Print simplified output to console
    echo "x Test 00 ran all file error cases" | tee -a "$LOG_FILE"
    
    echo "" >> "$LOG_FILE"
    echo "==============================" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
fi

# Process the rest of the test folders (excluding Test00)
for TEST_FOLDER in $(find "$TEST_DIR" -mindepth 1 -maxdepth 1 -type d -name "Test*" | sort); do
    TEST_NAME=$(basename "$TEST_FOLDER")
    
    # Skip Test00 as it was already handled separately
    if [ "$TEST_NAME" != "Test00_FilesDontExistOrWrongFormat" ] && [ -d "$TEST_FOLDER" ]; then
        # The exact file names as specified
        MAZE_FILE="$TEST_FOLDER/Maze2D.dat"
        PATH_FILE="$TEST_FOLDER/Path1D.dat"
        
        # Extract test number from folder name for better reporting
        TEST_NUM=$(echo "$TEST_NAME" | grep -o 'Test[0-9]*' | sed 's/Test//')
        
        # Log test information
        echo "Test Case $TEST_NUM: $TEST_NAME" | tee -a "$LOG_FILE"
        echo "Maze File: $MAZE_FILE" >> "$LOG_FILE"
        echo "Path File: $PATH_FILE" >> "$LOG_FILE"
        echo "------------------------------" >> "$LOG_FILE"
        
        # Run the executable with the test files
        if [ -f "$MAZE_FILE" ] && [ -f "$PATH_FILE" ]; then
            echo "Running: $EXECUTABLE $MAZE_FILE $PATH_FILE" >> "$LOG_FILE"
            echo "Output:" >> "$LOG_FILE"
            
            # Capture both output and exit status
            OUTPUT=$("$EXECUTABLE" "$MAZE_FILE" "$PATH_FILE" 2>&1)
            STATUS=$?
            
            echo "$OUTPUT" >> "$LOG_FILE"
            echo "Exit Status: $STATUS" >> "$LOG_FILE"
            
            # Print simplified output to console
            if [ $STATUS -eq 0 ]; then
                echo "✓ Test $TEST_NUM passed" | tee -a "$LOG_FILE"
            else
                echo "✗ Test $TEST_NUM failed (Exit Status: $STATUS)" | tee -a "$LOG_FILE"
            fi
        else
            echo "Error: Could not find maze file ($MAZE_FILE) or path file ($PATH_FILE)" | tee -a "$LOG_FILE"
        fi
        
        echo "" >> "$LOG_FILE"
        echo "==============================" >> "$LOG_FILE"
        echo "" >> "$LOG_FILE"
    fi
done

echo "All tests completed. Results saved to $LOG_FILE" | tee -a "$LOG_FILE"
