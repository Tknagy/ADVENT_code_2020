#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROBLEM=${DIR}/day-11
EXECUTABLE=${DIR}/a.out

# Compile
g++ -std=c++17 -I${DIR}/../../utils ${DIR}/main.cpp ${DIR}/../../utils/utils.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat ${DIR}/input-test.txt | $EXECUTABLE`)
TEST_RESULTS+=(37)
TEST_RESULTS+=(26)

# Input
TEST_CASES+=(`cat ${DIR}/input.txt | $EXECUTABLE`)
TEST_RESULTS+=(2448)
TEST_RESULTS+=(2234)

# Remove executable
rm $EXECUTABLE

# Check results
source ${DIR}/../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
