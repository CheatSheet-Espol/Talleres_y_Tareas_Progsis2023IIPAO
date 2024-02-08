#!/bin/bash

source $(dirname "$0")/globals

echo "Executing files test..."
echo 

#rm -f $EJECUTABLE
#make &>/dev/null
README="README.md"
echo "Checking $README"

if [ -e "$README" ] ; then
	lines=$(cat $README | wc -l)
	if [ "$lines" -ge 20 ] ; then
		echo -e "$PASS '$README' file exists. Its ok."
	else
		echo -e "$WARNING 'README.md' exists but its to simple. Need more information..."
		exit 2
	fi
else
	echo -e "$FAIL '$README' file not exists!"
	exit 1
fi

echo
echo


MAIN="main.c"
echo "Checking $MAIN"

if [ -e "$MAIN" ] ; then
	comments=$(cat $MAIN | grep -E "//|/\*" | wc -l)
	if [ "$comments" -ge 5 ] ; then
		echo -e "$PASS '$MAIN' file exists. Its ok."
	else
		echo -e "$WARNING '$MAIN' dont have enough comments..."
		exit 2
	fi
else
	echo -e "$FAIL '$MAIN' file not exists!"
	exit 1
fi

echo 

#PROGRAMA="programa"
#echo "Checking $PROGRAMA"

#if [ -e "$PROGRAMA" ] ; then
#	echo -e "$PASS '$PROGRAMA' file exists. Its ok."
#else
#	echo -e "$FAIL '$PROGRAMA' file not exists!"
#	exit 1
#fi

#echo

MAKE="Makefile"
echo "Checking $MAKE"

if [ -e "$MAKE" ] ; then
	echo -e "$PASS '$MAKE' file exists. Its ok."
else
	echo -e "$FAIL '$MAKE' file not exists!"
	exit 1
fi

echo


echo 
echo -e "$PASS basic file test...  :) "
echo
