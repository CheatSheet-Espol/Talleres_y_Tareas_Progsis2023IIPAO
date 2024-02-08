CC=gcc
CFLAGS=-c -I.

programa: main.o 
	$(CC) -o programa main.o


main.o: main.c
	$(CC) $(CFLAGS) main.c

.PHONY: clean
clean:
	rm *.o programa
