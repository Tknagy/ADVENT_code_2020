#!/bin/bash

PROBLEM="day-02"
EXECUTABLE="a.out"

# Compile
g++ -std=c++17 02.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat 02-input-test.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(2)
TEST_RESULTS+=(1)

# Input
TEST_CASES+=(`cat 02-input.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(638)
TEST_RESULTS+=(699)

# Remove executable
rm $EXECUTABLE

# Check results
source ../../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
