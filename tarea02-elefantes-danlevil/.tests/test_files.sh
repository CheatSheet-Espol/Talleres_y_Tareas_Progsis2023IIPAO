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
	comments=$(cat $MAIN | grep // | wc -l)
	if [ "$comments" -ge 2 ] ; then
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

FUNCTIONS="funciones.c"
echo "Checking $FUNCTIONS"

if [ -e "$FUNCTIONS" ] ; then
	comments=$(cat $FUNCTIONS | grep // | wc -l)
	if [ "$comments" -ge 3 ] ; then
		echo -e "$PASS '$FUNCTIONS' file exists. Its ok."
	else
		echo -e "$WARNING '$FUNCTIONS' dont have enough comments..."
		exit 2
	fi
else
	echo -e "$FAIL '$FUNCTIONS' file not exists!"
	exit 1
fi

echo

HEADER="funciones.h"
echo "Checking $HEADER"

if [ -e "$HEADER" ] ; then
	echo -e "$PASS '$HEADER' file exists."
else
	echo -e "$FAIL '$HEADER' file not exists!"
	exit 1
fi

echo 
echo -e "$PASS basic test...  :) "
echo
