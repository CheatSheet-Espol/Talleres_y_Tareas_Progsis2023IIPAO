#!/bin/bash

source $(dirname "$0")/globals


README="README.md"
echo "Checking $README file"

if [ -e "$README" ] ; then
	comments=$(cat $README | grep -E "imagenes" | wc -l)
	if [ "$comments" -ge 2 ] ; then
		echo -e "$PASS '$README' file its ok."
	else
		echo -e "$FAIL '$README' Table dont have your screenshot image!"
		exit 1
	fi
else
	echo -e "$FAIL '$README' file not exists!"
	exit 1
fi

echo 

echo "Checking images files"

comments=$(ls imagenes/ | wc -l)
if [ "$comments" -ge 2 ] ; then
	echo -e "$PASS Have all images."
else
	echo -e "$FAIL Missing images files."
	exit 1
fi

echo 
