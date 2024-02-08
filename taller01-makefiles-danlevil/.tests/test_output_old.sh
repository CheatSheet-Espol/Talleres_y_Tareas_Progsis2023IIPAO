#!/bin/bash

source $(dirname "$0")/globals

echo "Running output test..."
echo

rm $EJECUTABLE
make &>/dev/null

words=$(cat $TEST_FILE | wc -w)

output=$(./programa <<< $TEST_FILE)
expected_output="Please, enter a file name: Reading file information.txt...
The file '$TEST_FILE' has $words words."

if [ $? -eq 0 ]; then
	echo -e "$PASS Program run without errors"
else
	echo -e "$FAIL Program dont run"
	exit 1
fi

if [ "$output" == "$expected_output" ] ; then
  echo -e "$PASS Output is correct"
else
  echo -e "$FAIL Expected [$expected_output] but got: [$output]"
  exit 1
fi

echo
echo -e "$PASS All tests was ok."

exit 0
