[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/zPvg9_Ci)

# Contador de Palabras

Programa en C, con nombre "programa", lo que hace es contar las palabras  en un archivo de texto, permitiendo al usuario especificar la longitud mínima de las palabras a considerar. La funcionalidad principal del programa radica en analizar un archivo de texto dado y contar las palabras que cumplen con el requisito de longitud mínima establecido.

## Uso

El programa se puede ejecutar desde la línea de comandos con opciones que incluyen:

- `-c N`: Establecer la longitud mínima de las palabras a contar.
- `-f filename`: Especificar el nombre del archivo.

Además, el programa proporciona una opción de ayuda (`-h`) que muestra información detallada sobre cómo utilizarlo.

### Ejemplo de uso
~~~bash
./programa -c 5 -f mi_archivo.txt
~~~

## Compilación

Para compilar el programa, se puede utilizar el comando "make" desde la terminal

```bash
make
```