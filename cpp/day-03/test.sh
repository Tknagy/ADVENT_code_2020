#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROBLEM=${DIR}/day-03
EXECUTABLE=${DIR}/a.out

# Compile
g++ -std=c++17 ${DIR}/main.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat ${DIR}/input-test.txt | $EXECUTABLE`)
TEST_RESULTS+=(7)
TEST_RESULTS+=(336)

# Input
TEST_CASES+=(`cat ${DIR}/input.txt | $EXECUTABLE`)
TEST_RESULTS+=(198)
TEST_RESULTS+=(5140884672)

# Remove executable
rm $EXECUTABLE

# Check results
source ${DIR}/../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
