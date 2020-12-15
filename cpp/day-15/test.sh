#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROBLEM=${DIR}/day-15
EXECUTABLE=${DIR}/a.out

# Compile
g++ -std=c++17 -I${DIR}/../../utils ${DIR}/main.cpp ${DIR}/../../utils/utils.cpp -o $EXECUTABLE

###############################################################################
# Examples
###############################################################################
TEST_CASES+=(`cat ${DIR}/input-test-1.txt | $EXECUTABLE`)
TEST_RESULTS+=(436)
TEST_RESULTS+=(175594)

TEST_CASES+=(`cat ${DIR}/input-test-2.txt | $EXECUTABLE`)
TEST_RESULTS+=(1)
TEST_RESULTS+=(2578)

TEST_CASES+=(`cat ${DIR}/input-test-3.txt | $EXECUTABLE`)
TEST_RESULTS+=(10)
TEST_RESULTS+=(3544142)

TEST_CASES+=(`cat ${DIR}/input-test-4.txt | $EXECUTABLE`)
TEST_RESULTS+=(27)
TEST_RESULTS+=(261214)

TEST_CASES+=(`cat ${DIR}/input-test-5.txt | $EXECUTABLE`)
TEST_RESULTS+=(78)
TEST_RESULTS+=(6895259)

TEST_CASES+=(`cat ${DIR}/input-test-6.txt | $EXECUTABLE`)
TEST_RESULTS+=(438)
TEST_RESULTS+=(18)

TEST_CASES+=(`cat ${DIR}/input-test-7.txt | $EXECUTABLE`)
TEST_RESULTS+=(1836)
TEST_RESULTS+=(362)

###############################################################################
# Input
###############################################################################
TEST_CASES+=(`cat ${DIR}/input.txt | $EXECUTABLE`)
TEST_RESULTS+=(662)
TEST_RESULTS+=(37312)

# Remove executable
rm $EXECUTABLE

# Check results
source ${DIR}/../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
