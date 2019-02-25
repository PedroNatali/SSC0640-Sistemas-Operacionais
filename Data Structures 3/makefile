CC=gcc
CFLAGS=-I.
DEPS = funcionalidades.h
OBJ = funcionalidades.o progtrab.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

progtrab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o


