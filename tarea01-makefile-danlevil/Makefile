CC= gcc
CFLAGS= -c -I.

conversorKms: distanceFunc.o main.o
	$(CC) -o conversorKms distanceFunc.o main.o

distanceFunc.o: distanceFunc.c 
	$(CC) $(CFLAGS) distanceFunc.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean: 
	rm *.o 