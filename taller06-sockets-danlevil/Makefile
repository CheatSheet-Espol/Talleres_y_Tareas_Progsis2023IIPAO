DEPS = common.h sha256.h
CFLAGS = -Wall -c

.PHONY: all debug sanitize clean
all: server client

server: server.o common.o sha256.o $(DEPS)
	gcc -o $@ server.o common.o sha256.o $(DFLAGS)

client: client.o common.o $(DEPS)
	gcc -o $@ client.o common.o $(DFLAGS)

%.o: %.c $(DEPS)
	gcc $(CFLAGS) $< $(DFLAGS)

# Compila usando la opción -g para facilitar la depuración con gdb.
debug: DFLAGS = -g
debug: clean all

# Compila habilitando la herramienta AddressSanitizer para
# facilitar la depuración en tiempo de ejecución.
sanitize: DFLAGS = -fsanitize=address,undefined
sanitize: clean all

clean:
	rm -rf server client *.o
