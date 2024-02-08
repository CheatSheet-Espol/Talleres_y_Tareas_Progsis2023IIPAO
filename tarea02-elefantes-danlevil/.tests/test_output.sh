#!/bin/bash

source $(dirname "$0")/globals

echo "Checking results..."
echo 

rm -f $EJECUTABLE
make &>/dev/null


if [ -e "$EJECUTABLE" ] ; then
	echo -e "$PASS '$EJECUTABLE' file exists."
else
	echo -e "$FAIL '$EJECUTABLE' file not exists!"
	exit 1
fi

echo 

echo "Comparing results..."

#output=$(echo "$TEST_FILE" | ./programa)
output=$(./$EJECUTABLE <<< $TEST_FILE)
expected_output="Peso promedio: 6840.02"

if [ "$output" == "$expected_output" ] ; then
        echo -e "$PASS Right Result"
else
        echo -e "$FAIL Wrong Result."
		echo -e "$FAIL Expected [$expected_output] but got: [$output]"
	exit 1
fi

echo

echo 
echo -e "$PASS basic test... commit/push your files :) "
echo
