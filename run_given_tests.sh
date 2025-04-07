#!/bin/bash

# Path to the executable
EXECUTABLE="./build/src/Maze_solver"

# Directory containing test cases
TEST_DIR="./tests/TestCases/test"

# Log file
LOG_FILE="maze_solver_results.log"

# Create or clear log file
echo "Maze Solver Test Results" > "$LOG_FILE"
echo "========================" >> "$LOG_FILE"
echo "Date: $(date)" >> "$LOG_FILE"
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
    
    # Try to find the TestCases directory anywhere in the current directory tree
    FOUND_DIR=$(find . -type d -name "TestCases" -print -quit)
    
    if [ -n "$FOUND_DIR" ]; then
        TEST_DIR="${FOUND_DIR}/test"
        echo "Found alternative test directory: $TEST_DIR" | tee -a "$LOG_FILE"
        
        if [ ! -d "$TEST_DIR" ]; then
            echo "Error: 'test' subdirectory not found in $FOUND_DIR" | tee -a "$LOG_FILE"
            exit 1
        fi
    else
        echo "Error: Could not find TestCases directory" | tee -a "$LOG_FILE"
        exit 1
    fi
fi

# Count total test cases
TOTAL_TESTS=$(find "$TEST_DIR" -mindepth 1 -maxdepth 1 -type d | wc -l)
echo "Running $TOTAL_TESTS test cases..." | tee -a "$LOG_FILE"
echo "" >> "$LOG_FILE"

# Process each test folder in order 
# We use find with sort to ensure they run in the correct order
for TEST_FOLDER in $(find "$TEST_DIR" -mindepth 1 -maxdepth 1 -type d | sort); do
    if [ -d "$TEST_FOLDER" ]; then
        TEST_NAME=$(basename "$TEST_FOLDER")
        
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
