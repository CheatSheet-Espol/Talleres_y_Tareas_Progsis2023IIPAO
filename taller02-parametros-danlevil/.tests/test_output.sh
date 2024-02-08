#!/bin/bash

#NO MODIFICAR ESTE ARCHIVO! RP!

source $(dirname "$0")/globals

rm $EJECUTABLE
make &>/dev/null

if [ $? -eq 0 ] ; then
  echo -e "$PASS Compilación exitosa"
else
  echo -e "$FAIL Error de compilación"
  exit 1
fi

ARGUMENTOS="zambrano 1 bonilla 0 prueba 2 pizza"

if [ $1 == as ]; then
    echo "Probando output orden ascendente..."
    OPCION="-a"
    expected_output="Argumento no-opción: 0
Argumento no-opción: 1
Argumento no-opción: 2
Argumento no-opción: bonilla
Argumento no-opción: pizza
Argumento no-opción: prueba
Argumento no-opción: zambrano"
elif [ $1 == ds ]; then
    echo "Probando output orden descendente..."
    OPCION="-d"
    expected_output="Argumento no-opción: zambrano
Argumento no-opción: prueba
Argumento no-opción: pizza
Argumento no-opción: bonilla
Argumento no-opción: 2
Argumento no-opción: 1
Argumento no-opción: 0"
elif [ $1 == ay ]; then
	echo "Probando mensaje ayuda"
	OPCION="-h"
	ARGUMENTOS=""
	expected_output="Programa en C ejemplo, imprime argumentos ingresados en consola.
uso:
 ./programa [-i] [-e] [-a] [-d] [arg 1] [arg 2] ... [arg n]
 ./programa -h
Opciones:
 -h			Ayuda, muestra este mensaje
 -e			Switch to english
 -i			Ingresa una línea de texto
 -a			Imprime argumentos en orden ascendente
 -d			Imprime argumentos en orden descendente"
else
	echo -e "$FAIL Test invalido"
  	exit 1
fi

output=$(./$EJECUTABLE $OPCION $ARGUMENTOS)

if [ "$output" == "$expected_output" ] ; then
        echo -e "$PASS salida correcta"
else
        echo -e "$FAIL Programa con salida inesperada..."
        exit 1
fi

echo
