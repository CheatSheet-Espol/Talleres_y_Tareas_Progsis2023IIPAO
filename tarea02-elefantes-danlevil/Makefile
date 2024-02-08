CC= gcc
CFLAGS= -c -I.

promedio: funciones.o main.o
	$(CC) -o promedio funciones.o main.o

funciones.o: funciones.c funciones.h 
	$(CC) $(CFLAGS) funciones.c

main.o: main.c funciones.h
	$(CC) $(CFLAGS) main.c

clean: 
	rm *.o 
	rm promedio