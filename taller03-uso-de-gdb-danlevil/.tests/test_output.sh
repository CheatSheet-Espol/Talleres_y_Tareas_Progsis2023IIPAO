#!/bin/bash



source $(dirname "$0")/globals

rm $EJECUTABLE
make &>/dev/null

if [ $? -eq 0 ] ; then
  echo -e "$PASS Compilación exitosa"
else
  echo -e "$FAIL Error de compilación"
  exit 1
fi

ARCHIVO="datos_con_cabecera.txt"

if [ $1 == normal ]; then
  echo "Probando output con archivo con cabecera..."
  OPCION="-c"
  expected_output="Abriendo el archivo datos_con_cabecera.txt y asumiendo que tiene cabecera.
12	25	20	24.11
12	25	19	25.34
12	25	18	26.50
12	25	17	27.00
12	25	16	27.10
12	25	15	26.99
12	25	14	24.68
12	25	13	24.57"
elif [ $1 == invalido ]; then
  echo "Probando output con archivo invalido..."
  OPCION=""
  expected_output="Error al leer datos_con_cabecera.txt"
  stderr_output=$(./$EJECUTABLE $OPCION $ARCHIVO 2>&1 > /dev/null)
  if [ "$stderr_output" == "$expected_output" ] ; then
    echo -e "$PASS salida sterr correcta"
    exit 0
  else
    echo -e "$FAIL Programa con salida stderr inesperada..."
    exit 1
  fi
else
	echo -e "$FAIL Test invalido"
  exit 1
fi

output=$(./$EJECUTABLE $OPCION $ARCHIVO)

if [ "$output" == "$expected_output" ] ; then
  echo -e "$PASS salida correcta"
else
  echo -e "$FAIL Programa con salida inesperada..."
  exit 1
fi

echo
