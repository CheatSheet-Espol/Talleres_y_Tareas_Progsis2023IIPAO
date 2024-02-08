EXEC = secret
DEPS = blowfish.h
LIBS = libsha1.a

$(EXEC): main.o blowfish.o $(DEPS) $(LIBS)
	gcc -o $@ main.o blowfish.o $(LIBS) $(DFLAGS)

main.o: main.c $(DEPS)
	gcc -c $< $(DFLAGS)

blowfish.o: blowfish.c $(DEPS)
	gcc -c $< $(DFLAGS)

.PHONY: sanitize debug clean
debug: DFLAGS = -g
debug: clean $(EXEC)

sanitize: DFLAGS = -fsanitize=address,undefined
sanitize: clean $(EXEC)

clean:
	rm -rf $(EXEC) *.o *.enc *.dec



