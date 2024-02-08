#!/bin/bash

source $(dirname "$0")/globals

EJECUTABLES="server client"
PUERTO=7070

clean(){
	make clean &>/dev/null
	rm -f $EJECUTABLES
	rm -f test
}

clean_fail(){
	clean
	echo -e "$FAIL " $1
	exit 1
}

clean
make &>/dev/null

if [ $? -eq 0 ] ; then
	echo -e "$PASS Compilación exitosa"
else
	clean_fail "Error de compilación"
fi

./server "$PUERTO" &

RANDOM_TXT=$(tr -dc "a-z" </dev/urandom | head -c 10)
HASH=$(echo -n $RANDOM_TXT | sha256sum | tr -d " -")

./client 127.0.0.1 "$PUERTO" -t "$RANDOM_TXT"

if [ $? -eq 0 ] ; then
	echo -e "$PASS Comunicación exitosa"
else
	clean_fail "Error de comunicación"
fi

echo "Texto de prueba enviado a servidor: $RANDOM_TXT"
OUTPUT=$(cat test)
echo "Respuesta de servidor: $OUTPUT"
echo "Respuesta esperada de servidor: $HASH"

if [ "$OUTPUT" == "$HASH" ] ; then
	echo -e "$PASS Hashing exitoso"
else
	clean_fail "Error de hashing"
fi

clean
echo
