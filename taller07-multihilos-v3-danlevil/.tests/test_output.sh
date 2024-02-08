#!/bin/bash

source $(dirname "$0")/globals

EJECUTABLES="server client"
PUERTO=7070

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

./server "$PUERTO" &>/dev/null &

PID_SERVER=$(pgrep server)

if [ -z "$PID_SERVER" ] ; then
	clean_fail "No se pudo comprobar proceso servidor" 
else
	echo -e "$PASS Servidor online con PID: $PID_SERVER"
fi

nc -w1 127.0.0.1 "$PUERTO" &
nc -w1 127.0.0.1 "$PUERTO" &

echo "Ejecutando 2 clientes..."

N_PROCS=$(pgrep server | wc -l)
echo "Procesos: $N_PROCS"

N_THREADS=$(cat "/proc/$PID_SERVER/status" | grep -i Threads | awk {'print $2'})
echo "Hilos: $N_THREADS"


if [ "$N_THREADS" -lt 3 ] ; then
	clean_fail "No se han creado suficientes hilos"
else
	echo -e "$PASS Creación de hilos exitosa"
fi

clean
