hash: main.c
	gcc -static -o hash main.c ./libsha1.a
hash_dyn: main.c
	#TO-DO: Compilación con linking dinámico
	#incluir al comando -->  -Wl,-rpath,. -L. -lsha1
	gcc -o hash_dyn main.c ./libsha1.so -Wl,-rpath,. -L. -lsha1
	
.PHONY: clean
clean:
	rm -rf hash hash_dyn
