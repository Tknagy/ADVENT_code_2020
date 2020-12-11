#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROBLEM=${DIR}/day-10
EXECUTABLE=${DIR}/a.out

# Compile
g++ -std=c++17 -I${DIR}/../../utils ${DIR}/main.cpp ${DIR}/../../utils/utils.cpp -o $EXECUTABLE

# Example
TEST_CASES+=(`cat ${DIR}/input-test.txt | $EXECUTABLE`)
TEST_RESULTS+=(35)
TEST_RESULTS+=(8)

# Example 2
TEST_CASES+=(`cat ${DIR}/input-test-2.txt | $EXECUTABLE`)
TEST_RESULTS+=(220)
TEST_RESULTS+=(19208)

# Input
TEST_CASES+=(`cat ${DIR}/input.txt | $EXECUTABLE`)
TEST_RESULTS+=(2263)
TEST_RESULTS+=(396857386627072)

# Remove executable
rm $EXECUTABLE

# Check results
source ${DIR}/../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
