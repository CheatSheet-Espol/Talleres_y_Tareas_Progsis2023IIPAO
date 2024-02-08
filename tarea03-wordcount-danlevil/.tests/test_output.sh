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
echo 

wc_file=$(cat $TEST_FILE | wc -w)
output0=$(./$EJECUTABLE -c 0 -f $TEST_FILE)
output1=$(./$EJECUTABLE -c 5 -f $TEST_FILE)
output2=$(./$EJECUTABLE -c 10 -f $TEST_FILE)

#expect1 = $(awk -v n=5 '{for (i=1; i<=NF; i++) if (length($i) >= n) print $i}' $TEST_FILE | wc -l)
#expect2 = $(awk -v n=10 '{for (i=1; i<=NF; i++) if (length($i) >= n) print $i}' $TEST_FILE | wc -l)

expected_output0="The number of words with length>=0 in '$TEST_FILE' file is 105."
expected_output1="The number of words with length>=5 in '$TEST_FILE' file is 47."
expected_output2="The number of words with length>=10 in '$TEST_FILE' file is 6."

echo "For -c 0..."
if [ "$output0" == "$expected_output0" ] ; then
	echo -e "$PASS Right Result"
else
	echo -e "$FAIL Wrong Result."
	echo -e "$FAIL for -c 0 Expected [$expected_output0] but got: [$output0]"
	exit 1
fi
echo 

echo "For -c 5..."
if [ "$output1" == "$expected_output1" ] ; then
	echo -e "$PASS Right Result"
else
	echo -e "$FAIL Wrong Result."
	echo -e "$FAIL for -c 5 Expected [$expected_output1] but got: [$output1]"
	exit 1
fi
echo

echo "For -c 10..."
if [ "$output2" == "$expected_output2" ] ; then
	echo -e "$PASS Right Result"
else
	echo -e "$FAIL Wrong Result."
	echo -e "$FAIL for -c 10 Expected [$expected_output2] but got: [$output2]"
	exit 1

fi


echo

echo 
echo -e "$PASS Output Results... commit/push your files :) "
echo
