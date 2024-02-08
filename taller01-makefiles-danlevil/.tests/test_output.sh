#!/bin/bash

source $(dirname "$0")/globals

echo "Executing test output program..."
echo 

rm $EJECUTABLE
make &>/dev/null

echo "Creating test file..."
#tr -dc "a-z \n" </dev/urandom | head -c 256 > $TEST_FILE
if [ -e $TEST_FILE ] ; then
	words=$(cat $TEST_FILE | wc -w)
	echo "The file exists and it has $words words."
else
	echo -e "$FAIL The file '$TEST_FILE' not exists..."
	exit 1
fi

echo
echo "Comparing count words in '$TEST_FILE' ..."
#output=$(echo "$TEST_FILE" | ./programa)
output=$(./programa <<< $TEST_FILE)
expected_output="Please, enter a file name: Reading file information.txt...
The file 'information.txt' has $words words."

if [ "$output" == "$expected_output" ] ; then
        echo -e "$PASS Right counting"
else
        echo -e "$FAIL Wrong counts of words or unexpected output..."
		echo -e "$FAIL Expected [$expected_output] but got: [$output]"
	exit 1
fi

echo
