#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROBLEM=${DIR}/day-18
EXECUTABLE=${DIR}/a.out

# Compile
g++ -std=c++17 -I${DIR}/../../utils ${DIR}/main.cpp ${DIR}/../../utils/utils.cpp -o $EXECUTABLE

###############################################################################
# Examples
###############################################################################
TEST_CASES+=(`cat ${DIR}/input-test-1.txt | $EXECUTABLE`)
TEST_RESULTS+=(71)
TEST_RESULTS+=(231)

TEST_CASES+=(`cat ${DIR}/input-test-2.txt | $EXECUTABLE`)
TEST_RESULTS+=(51)
TEST_RESULTS+=(51)

TEST_CASES+=(`cat ${DIR}/input-test-3.txt | $EXECUTABLE`)
TEST_RESULTS+=(26)
TEST_RESULTS+=(46)

TEST_CASES+=(`cat ${DIR}/input-test-4.txt | $EXECUTABLE`)
TEST_RESULTS+=(437)
TEST_RESULTS+=(1445)

TEST_CASES+=(`cat ${DIR}/input-test-5.txt | $EXECUTABLE`)
TEST_RESULTS+=(12240)
TEST_RESULTS+=(669060)

TEST_CASES+=(`cat ${DIR}/input-test-6.txt | $EXECUTABLE`)
TEST_RESULTS+=(13632)
TEST_RESULTS+=(23340)

TEST_CASES+=(`cat ${DIR}/input-test-7.txt | $EXECUTABLE`)
TEST_RESULTS+=(40089)
TEST_RESULTS+=(717513)

###############################################################################
# Input
###############################################################################
TEST_CASES+=(`cat ${DIR}/input.txt | $EXECUTABLE`)
TEST_RESULTS+=(23507031841020)
TEST_RESULTS+=(218621700997826)

# Remove executable
rm $EXECUTABLE

# Check results
source ${DIR}/../../assert.sh
for i in ${!TEST_CASES[@]}; do
    assert "echo ${TEST_CASES[$i]}" "${TEST_RESULTS[$i]}"
done
assert_end ${PROBLEM}
