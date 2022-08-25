CC = g++

CFLAGS = -c -Wall

BLD_NAME = build
BLD_TYPE = dev
BLD_VERSION = 0.1
BLD_FORMAT = .out

ROOTSOLVER_UNI_NAME = rootsolver.unitest
ROOTSOLVER_TESTS = rootsolver_unitest.txt
ROOTSOLVER_UNI_LOG = rootsolver_uni.log

#TODO: learn about g++ -M_ (something to do with headers, includes, makefiles e.t.c.)

all: main

main: main.o mainio.o rootsolver.o debug.o logger.o argparser.o utils.o
	$(CC) main.o mainio.o rootsolver.o debug.o logger.o argparser.o utils.o -o $(BLD_NAME)_v$(BLD_VERSION)_$(BLD_TYPE)$(BLD_FORMAT)

run:
	./$(BLD_NAME)_v$(BLD_VERSION)_$(BLD_TYPE)$(BLD_FORMAT)

test: rootsolver_unitest.o rootsolver.o debug.o logger.o utils.o
	$(CC) rootsolver_unitest.o rootsolver.o debug.o logger.o utils.o -o $(ROOTSOLVER_UNI_NAME)
	./$(ROOTSOLVER_UNI_NAME) > $(ROOTSOLVER_UNI_LOG) 2>&1 < $(ROOTSOLVER_TESTS)

rootsolver_unitest.o:
	$(CC) $(CFLAGS) rootsolver_unitest.cpp

main.o:
	$(CC) $(CFLAGS) main.cpp

mainio.o:
	$(CC) $(CFLAGS) mainio.cpp

rootsolver.o:
	$(CC) $(CFLAGS) rootsolver.cpp

debug.o:
	$(CC) $(CFLAGS) debug.cpp

logger.o:
	$(CC) $(CFLAGS) logger.cpp

argparser.o:
	$(CC) $(CFLAGS) argparser.cpp

utils.o:
	$(CC) $(CFLAGS) utils.cpp

clean:
	rm -rf *.o

rm: clean
	rm -rf *.log *.out $(ROOTSOLVER_UNI_NAME)