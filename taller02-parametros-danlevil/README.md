[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/p1V_uVYc)
# Plantilla genérica repositorio C
Plantilla genérica para repositorios de proyectos desarrollados en el lenguaje C usando GCC y Make en LINUX.

## Descripción
Este programa contiene código ejemplo de uso de lo siguiente:
* Documentación de un repositorio usando *README.md*
* Uso de un *Makefile* para compilar varios archivos
* Uso de *.gitignore* (archivos que se excluyen en el commit)
* Parsing de opciones y argumentos usando *getopt*
* Ingreso de texto desde consola usando *getline()*

## Uso del programa
El programa tiene el siguiente funcionamiento:
```
$ ./programa -h
Programa en C ejemplo, imprime argumentos ingresados en consola.
uso:
 ./programa [-i] [-e] [arg 1] [arg 2] ... [arg n]
 ./programa -h
Opciones:
 -h			Ayuda, muestra este mensaje
 -e			Switch to english
 -i			Ingresa una línea de texto
```

Ejemplo de ejecución:
```
$ ./programa -i hola mundo
Argumento no-opción: hola
Argumento no-opción: mundo
Ingrese texto: que hay!
que hay!
```
Otro ejemplo de ejecución, usando -e:
```
./programa -ie hola mundo
Non-option argument: hola
Non-option argument: mundo
Input text: hola todos!
hola todos!
```

## Ejemplos de código en el programa
El archivo [input.h](input.h) muestra un ejemplo de documentación de una función:
```C
/**
 * Función get_from_console muestra una forma segura de ingresar una linea de texto desde consola.
 * IMPORTANTE: line debe ser liberado con free() después de su uso.
 *
 * @param line Cadena de carecteres a ser llenada por getline. Este parametro será llenado con
 *             toda la línea de texto ingresada sin incluir el salto de línea '\n'.
 *
 * @return Número de caracteres en la línea de texto, no considera '\n'. -1 si hubo error.
 */
int get_from_console(char **line);
```
En el archivo [input.c](input.c) se muestra el uso de *getline()* para ingresar texto desde consola:
```C
int get_from_console(char **line)
{
	*line = NULL; //Importante inicializar en NULL
	size_t n = 0; //Obliga a getline a usar malloc()
	ssize_t l = 0; //Número de caracteres ingresados, incluye '\n'

	if(eflag)
		printf("Input text: ");
	else
		printf("Ingrese texto: ");

	l = getline(line, &n, stdin); //getline llama a malloc internamente

	if(l > 0)
		(*line)[l-1] = '\0'; //Sobreescribe el salto de línea
	else
		return l;

	return l-1;
}
```
## Compilación
Para compilar el programa:
```
$ make
```
Para compilar facilitando la depuración con gdb:
```
$ make debug
```
Para compilar habilitando la herramienta AddressSanitizer, facilita la depuración en tiempo de ejecución:
```
$ make sanitize
```
