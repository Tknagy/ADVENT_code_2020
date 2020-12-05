#!/bin/bash

PROBLEM="day-04"
EXECUTABLE="a.out"

# Compile
g++ -std=c++17 main.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat input-test.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(2)
TEST_RESULTS+=(2)

# Invalid
TEST_CASES+=(`cat input-invalid.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(4)
TEST_RESULTS+=(0)

# Valid
TEST_CASES+=(`cat input-valid.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(4)
TEST_RESULTS+=(4)

# Input
TEST_CASES+=(`cat input.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(226)
TEST_RESULTS+=(160)

# Remove executable
rm $EXECUTABLE

# Check results
source ../../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
