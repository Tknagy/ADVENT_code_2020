#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROBLEM=${DIR}/day-04
EXECUTABLE=${DIR}/a.out

# Compile
g++ -std=c++17 ${DIR}/main.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat ${DIR}/input-test.txt | $EXECUTABLE`)
TEST_RESULTS+=(2)
TEST_RESULTS+=(2)

# Invalid
TEST_CASES+=(`cat ${DIR}/input-invalid.txt | $EXECUTABLE`)
TEST_RESULTS+=(4)
TEST_RESULTS+=(0)

# Valid
TEST_CASES+=(`cat ${DIR}/input-valid.txt | $EXECUTABLE`)
TEST_RESULTS+=(4)
TEST_RESULTS+=(4)

# Input
TEST_CASES+=(`cat ${DIR}/input.txt | $EXECUTABLE`)
TEST_RESULTS+=(226)
TEST_RESULTS+=(160)

# Remove executable
rm $EXECUTABLE

# Check results
source ${DIR}/../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
