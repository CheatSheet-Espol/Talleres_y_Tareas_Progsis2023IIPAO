#!/bin/bash

source $(dirname "$0")/globals

echo "Excecuting Makefile test..."

make &>/dev/null

if [ $? -eq 0 ] ; then
  echo -e "$PASS No errors in compilation"
else
  echo -e "$FAIL Compilation error"
  exit 1
fi

echo
echo "Testing if Makefile always recompile..."

make -q

if [ $? -eq 0 ] ; then
	echo -e "$PASS Makefile not recompile"
else
	echo -e "$FAIL Makefile always recompile..."
	exit 1
fi

echo
echo "Testing if Makefile sense missing exec..."

rm $EJECUTABLE

make &>/dev/null

if [ -e "$EJECUTABLE" ] ; then
	echo -e "$PASS Makefile recompile if missing exec"
else
	echo -e "$FAIL Makefile not detect missing exec"
	exit 1
fi

echo
echo "Testing if Makefile detect modified code..."

sleep .1; touch "$FUNCIONES"
make -q

if [ $? -eq 0 ] ; then
        echo -e "$FAIL Makefile dont detect modified code"
	exit 1
else
        echo -e "$PASS Makefile detect modified code"
fi

make &>/dev/null

echo
echo "Testing if Makefile detects header modification..."

sleep .1; touch "$CABECERA"
make -q

if [ $? -eq 0 ] ; then
        echo -e "$FAIL Makefile dont detect header modification"
        exit 1
else
        echo -e "$PASS Makefile detect header modification"
fi

echo
echo "Testing if Makefile produce object files..."

make &>/dev/null

if [ -e "$OBJETO" ] ; then
        echo -e "$PASS Makefile produce object files"
else
        echo -e "$FAIL Makefile not produce object files"
        exit 1
fi

echo
