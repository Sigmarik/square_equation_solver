CC = g++

CFLAGS = -c -Wall

BLD_NAME = build
BLD_TYPE = dev
BLD_VERSION = 0.1
BLD_FORMAT = .out

all: main

main: main.o mainio.o rootsolver.o debug.o
	$(CC) main.o mainio.o rootsolver.o debug.o -o $(BLD_NAME)_v$(BLD_VERSION)_$(BLD_TYPE)$(BLD_FORMAT)
	./$(BLD_NAME)_v$(BLD_VERSION)_$(BLD_TYPE)$(BLD_FORMAT)

main.o:
	$(CC) $(CFLAGS) main.c

mainio.o:
	$(CC) $(CFLAGS) mainio.c

rootsolver.o:
	$(CC) $(CFLAGS) rootsolver.c

debug.o:
	$(CC) $(CFLAGS) debug.c

clean:
	rm -rf *.o