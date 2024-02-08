# Makefile completo --nada que modificar (ojearlo!)
DEPS = input.h

programa: main.o input.o
	gcc -o programa main.o input.o $(DFLAGS)

main.o: main.c $(DEPS)
	gcc -c main.c $(DFLAGS)

input.o: input.c $(DEPS)
	gcc -c input.c $(DFLAGS)

# Compila usando la opción -g para facilitar la depuración con gdb.
.PHONY: debug
debug: DFLAGS = -g
debug: clean programa

# Compila habilitando la herramienta AddressSanitizer para
# facilitar la depuración en tiempo de ejecución.
.PHONY: sanitize
sanitize: DFLAGS = -fsanitize=address,undefined
sanitize: clean programa

.PHONY: clean
clean:
	rm -rf programa *.o

.PHONY: run
run: programa
	./programa hola mundo
