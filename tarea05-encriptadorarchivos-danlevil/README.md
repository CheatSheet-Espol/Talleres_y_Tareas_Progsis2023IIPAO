[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/oEnWHoBr)
# Tarea05

La tarea consiste en mejorar el código del taller realizado de encriptación/desencriptación, deberá realizar las modificaciones necesarias para que ahora su código adicionalmente pueda encriptar/desencriptar todos los archivos dentro de una carpeta especificada

```
$ ./secret -h
secret encripta o desincripta un archivo o carpeta usando el algoritmo Blowfish.
uso:
 ./secret [-d] [-f] -k <key> <nombre_archivo|nombre_carpeta>
 ./secret -h
Opciones:
 -h			Ayuda, muestra este mensaje
 -d			Desencripta el archivo en lugar de encriptarlo.
 -f			Encripta/Desencripta una carpeta en vez de un archivo
 -k <key>		Específica la clave (key) de encriptación, 8 bytes en hex.
```

El argumento *<nombre_archivo|nombre_carpeta>* es obligatorio, y dependiendo si recibe la opción -f servirá para identificar si es el nombre de un archivo o una carpeta. 

## Ejemplos de uso
Si se desea desencriptar un archivo
```
./secret -d -k PALABRACLAVE archivo_encriptado.txt
```

Si se desea desencriptar una carpeta
```
./secret -d -k PALABRACLAVE carpeta_con_archivos -f
```

La palabra clave, deberá convertise a [SHA1](http://www.sha1-online.com/) y tomar los 16 primeros caracteres para luego transformarlos a connotación hexadecimal. Ej. 
```
si palabra clave es: secreto --> sha1 --> 0a4f8b93faad504007df78c9acb6f93ea6cc8c53
los primeros 16 caracteres serían: 0a4f8b93faad5040
```

Deberá crearse, en tiempo de ejecución, dos carpetas llamadas _archivos_encriptados_ y _archivos_desencriptados_ donde se guardarán los archivos dependiendo del caso. No poner la extensión .enc o .dec a los archivos. Las carpetas o archivos considerados para encriptaptación o desencriptación se encontrarán en la misma ruta del proyecto.

## Retos

1. Leer varios archivos de una carpeta
2. Encriptar/Desencriptar cada archivo leído


## Evaluacion

(aquí no hay Testfile)

* Crear carpetas. 1pt
* Leer achivos de carpeta. 1pt
* Convertir palabra clave a SHA1. 1pt
* Encriptar/Desencriptar todos archivos. 2pts
