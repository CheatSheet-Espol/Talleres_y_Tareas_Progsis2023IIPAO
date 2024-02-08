[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/8Oy9F0x7)
# Práctica uso de hilos
Práctica sobre uso básico de hilos en Linux usando C.

## Instrucciones
La práctica consiste en modificar una aplicación cliente - servidor que implementa una consola remota para que atienda varios clientes de manera simultánea usando hilos.

Este repositorio contiene código ejemplo de una aplicación cliente - servidor que implementa una consola remota básica. Es decir, los comandos que se envian desde el cliente al servidor son ejecutados en el servidor y su salida es enviada al cliente a través del socket de conexión. El servidor es multi-cliente usando procesos.

Es necesario efectuar las siguientes modificaciones:
1. Eliminar la funcionalidad muli-cliente con procesos y reemplazarla usando hilos.
2. Implementar la opción -d en el servidor para permitir que el proceso servidor se ejecute en segundo plano.

El programa servidor *server* debe tener el siguiente comportamiento:
```
$ ./server -h
Servidor simple de ejecución remota de comandos.
uso:
 ./server [-d] <puerto>
 ./server -h
Opciones:
 -h			Ayuda, muestra este mensaje
 -d			Funciona en modo daemon
```

El programa cliente *client* no debe ser modificado.

## Entregable
Modificar el código ejemplo en este repositorio para implementar la funcionalidad requerida. El servidor debe usar hilos para atender varios clientes de manera simultánea y soportar de manera correcta el modo de ejecución en segundo plano (modo *daemon*). 

## Compilación
Para compilar cliente y servidor:
```
$ make
```
Para compilar solo el servidor:
```
$ make server
```
Para compilar cliente y servidor facilitando la depuración con gdb:
```
$ make debug
```
Para compilar cliente y servidor habilitando la herramienta AddressSanitizer, facilita la depuración en tiempo de ejecución:
```
$ make sanitize
```
