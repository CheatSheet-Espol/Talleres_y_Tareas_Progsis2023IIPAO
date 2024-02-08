[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SYHWm_jd)
# Práctica uso de llamadas I/O
Práctica sobre uso básico de llamadas de sistema I/O en Linux usando C para la materia Programación de Sistemas de la ESPOL.

## Instrucciones
La práctica consiste en crear un programa en C que encripta o desencripta un archivo usando el algoritmo de encriptación [Blowfish](https://es.wikipedia.org/wiki/Blowfish). El programa usa la implementación del algoritmo de Blowfish en [crypto-algorithms](https://github.com/B-Con/crypto-algorithms). El programa debe tener el siguiente comportamiento:

```
$ ./secret -h
secret encripta o desincripta un archivo usando el algoritmo Blowfish.
uso:
 ./secret [-d] -k <key> <nombre_archivo>
 ./secret -h
Opciones:
 -h			Ayuda, muestra este mensaje
 -d			Desencripta el archivo en lugar de encriptarlo.
 -k <key>		Específica la clave (key) de encriptación, 8 bytes en hex.
```

El argumento *<nombre_archivo>* es obligatorio y especifica el nombre del archivo a encriptar/desencriptar. La opción *-d* es opcional y especifica que el archivo debe ser desencriptado, por defecto el archivo es encriptado. La opción *-k* es mandatoria y especifica la clave o key de encriptación/desencriptación. Por simplicidad, en este programa se aceptaran claves de 64 bits (8 bytes) u 16 caracteres hexadecimales. La clave será especificada como argumento de *-k* en formato hexadecimal. Recordar que todo argumento que reciba el main es considerado como un _string_.

## Ejemplos de uso
Para encriptar un archivo, ejemplo el archivo Makefile con la clave de encriptación FF00AA00B50012CD :
```
./secret -k FF00AA00B50012CD Makefile
Leyendo el archivo Makefile (540 bytes)...
Archivo Makefile encriptado exitosamente en Makefile.enc...
```
El programa debe crear un nuevo archivo encriptado con el nombre del archivo original y la extensión *.enc*.

Para desencriptar un archivo ya encriptado, por ejemplo *imagen_encriptada.png*, que fue encriptada con la clave 0102030405060708 :
```
$ ./secret -k 0102030405060708 imagen_encriptada.png -d
Leyendo el archivo imagen_encriptada.png (4480 bytes)...
Archivo imagen_encriptada.png desencriptado exitosamente en imagen_encriptada.png.dec...
```
El programa debe crear un nuevo archivo desencriptado con el nombre del archivo original y la extensión *.dec*.

## Retos
El _primer reto_ es *traducir* la clave especificada en la opción *-k* de ASCII Hex a su valor númerico byte por byte. Una forma es, en un arreglo de 8 bytes:
```C
BYTE key_arg[8];
```
usar el siguiente lazo para recorrer byte por byte la clave en ASCII *key_arg_str* y almacenar el valor de cada byte en *key_arg*:
```C
//Extraer valor númerico de la clave en ASCII hex....
unsigned short byte, i;
for(i=0;i<8;i++){
	sscanf(key_arg_str + 2*i,"%2hx", &byte);
	key_arg[i] = (BYTE) byte;
}
```

El _segundo reto_ es crear un archivo de salida nuevo con el nombre del archivo de entrada concatenando *.dec* o *.enc* al final del nombre. Usar *calloc, strcpy, strcat* para el nuevo nombre y la función *open* con las banderas *O_CREAT*, *O_TRUNC* y *O_WRONLY* para crear el archivo. Es importante asegurarse que el archivo nuevo tenga permisos de lectura y escritura para el usuario dueño (usar por ejemplo *S_IRUSR* y *S_IWUSR* en *open*).

El _tercer reto_ es leer el archivo de entrada bloque por bloque, desencriptar/encriptar, y escribir el archivo de salida bloque por bloque.

## Validacion

```
make -f Testfile encrypt
make -f Testfile decrypt
```
