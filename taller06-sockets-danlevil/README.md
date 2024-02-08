[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/weY5Q5Z3)
# Taller uso de sockets

## Instrucciones
La práctica consiste en crear una aplicación cliente - servidor para generar un hash SHA-256 a partir de una cadena de caracteres:
1. El cliente debe enviar al servidor la cadena de caracteres.
2. El servidor debe usar la cadena de caracteres recibida, ignorando el salto de línea al final, y generar un hash SHA-256. Usar [crypto-algorithms](https://github.com/B-Con/crypto-algorithms).
3. El servidor debe enviar el hash SHA-256 en formato ASCII Hex terminado con un salto de línea al cliente.

Nota1: Toda comunicación entre cliente y servidor debe ser enviada en modo ASCII con salto de línea al final.

Nota2: En equipos MACs puede existir inconvenientes con las librerías.

.

Para ejecutar el servidor se debe especificar como argumento el puerto TCP, por ejemplo:
```
$ ./server 8080
server escuchando en puerto 8080...
```

Asumiendo que el servidor esta corriendo en una maquina con la IP 192.168.100.12 en el puerto 8080, ejemplo de ejecución del cliente:
```
$ ./client 192.168.100.12 8080
Conectado exitosamente a 192.168.100.12 en el puerto 8080.
Ingrese texto para enviar al servidor, escriba CHAO para terminar...
> hola
Recibido: b221d9dbb083a7f33428d7c2a3c3198ae925614d70210e28716ccaa7cd4ddb79
> 
```
Si el servidor esta en la misma máquina, entonces es necesario abrir otra ventana/tab de terminal y ejecutar el cliente de esta forma:
```
$ ./client 127.0.0.1 8080
Conectado exitosamente a 127.0.0.1 en el puerto 8080.
Ingrese texto para enviar al servidor, escriba CHAO para terminar...
> 
```

## Código ejemplo
Este repositorio contiene código ejemplo de una aplicación *eco* cliente - servidor. Es decir, el usuario ingresa una línea de texto desde el cliente, el cliente la envia al servidor y el servidor la envia de regreso.

## Entregable
Modificar el código ejemplo en este repositorio para implementar la aplicación cliente - servidor de hashing SHA-256.

### TIPS
Es necesario modificar solamente el servidor, es decir el archivo *server.c*, agregar los archivos para implementar SHA-256 (ver [crypto-algorithms](https://github.com/B-Con/crypto-algorithms)). El Makefile ya cuenta con el respectivo header para incluir a la librería. Revisar el archivo _sha256_test.c_ para ver funcionamiento de la librería.

Además, es importante considerar que el hash debe ser enviado por el socket en formato ASCII Hex (en lugar de directamente en binario). Para esto, se puede usar la siguiente función (la cual convierte un buffer binario a una cadena de caracteres en ASCII Hex con un salto de línea al final):
```C
void sprint_hex(char *output, const unsigned char* input, size_t size)
{
    int i;
    for(i = 0; i < size; ++i)
        sprintf(output + 2*i, "%02x", input[i]);
    sprintf(output + 2*i, "\n");
}
```

No es necesario crear una librería estática ni dinámica del sha256, basta con incluir en la carpeta de su proyecto los archivos _sha256.h_ y _sha256.c_ para que el makefile en el proceso gcc genere los respectivos ejecutables.


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

## Test
Para probar el test de autocalificación (puede demorar hasta 5min en autocalificar en repositorio):
```
$ make -f Testfile
```
Es posible que para equipos MACs, la librería muestre error.
