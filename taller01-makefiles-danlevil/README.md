[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/nLHiv88w)
# ProgSist-Taller01 - Contador simple de palabras

Este repositorio debe ser **CLONADO** en su máquina local.

Recordar generar un token con TODOS los permisos (usarlo como contraseña)

## Ejemplo del funcionamiento del programa.

Asuma que tiene un archivo llamado _information.txt_

```
Programacion de Sistemas
Sean todo bienvenidos
Vamos a contar palabras en 
este es un archivo de pruebas
```

Se debe tener un programa que al leer un archivo, debe mostrar la siguiente informacion:

```
$./programa
Please, enter a file name: information.txt
Reading file information.txt...
The file 'information.txt' has 17 words.
```

# Compilación con Make

El archivo Makefile debe ser modificado para compilar el programa de manera eficiente, es decir:
1. El ejecutable debe llamarse **programa** y make debe ser sensible a la ausencia del ejecutable.
2. make debe ser sensible a modificaciones individuales de los archivos .c y recompilar únicamente el archivo modifcado.
3. make debe ser sensible a modificaciones de los archivos cabecera .h y recompilar todos los archivos que dependan de él.
4. make NO debe recompilar ningún archivo que no haya sido modificado


Para compilar el programa:

```
$ make
```

Para limpiar archivos temporales

```
$ make clean
```

Para probar que el _make_ funciona correctamente:

```
$ make -f Testfile Makefile
```

Para probar que el _programa_ funciona correctamente:

```
$ make -f Testfile Output
```

# Entregable

Modificar solamente los archivos (ojear también main.c):

1. Makefile
2. functions.c

Deberá realizar un commit cada vez que modifique un archivo, es decir, deberá realizar al menos dos commits.

Nota: Su repositorio NO debe contener archivos compilados .o, ni el archivo ejecutable (ejecutar _clean_ antes de subir sus cambios).
