#!/bin/bash

source $(dirname "$0")/globals

EJECUTABLES="server client"
PUERTO=7070
N_WORKERS=10

clean(){
	pkill -2 server
	make clean &>/dev/null
	rm -f $EJECUTABLES
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

./server -d -j "$N_WORKERS" "$PUERTO"

PID_SERVER=$(pgrep server)
PID_SERVER=$(echo $PID_SERVER)

if [ -z "$PID_SERVER" ] ; then
	clean_fail "No se pudo comprobar proceso servidor" 
else
	echo -e "$PASS Servidor online con PID: $PID_SERVER"
fi

N_THREADS=$(cat "/proc/$PID_SERVER/status" | grep -i Threads | awk {'print $2'})
echo "Hilos: $N_THREADS"

EXPECTED_THREADS=$((N_WORKERS + 1))

if [ "$N_THREADS" -eq "$EXPECTED_THREADS" ] ; then
	echo -e "$PASS Creación de hilos exitosa"
else
	clean_fail "No se han creado suficientes hilos"
fi

clean
