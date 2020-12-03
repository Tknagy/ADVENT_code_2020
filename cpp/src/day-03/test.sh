#!/bin/bash

PROBLEM="day-03"
EXECUTABLE="a.out"

# Compile
g++ -std=c++17 main.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat input-test.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(7)
TEST_RESULTS+=(336)

# Input
TEST_CASES+=(`cat input.txt | ./$EXECUTABLE`)
TEST_RESULTS+=(198)
TEST_RESULTS+=(5140884672)

# Remove executable
rm $EXECUTABLE

# Check results
source ../../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
