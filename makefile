CC = g++

CFLAGS = -c -Wall

BLD_FOLDER = build
TEST_FOLDER = test

BLD_NAME = build
BLD_VERSION = 0.1
BLD_PLATFORM = linux
BLD_TYPE = dev
BLD_FORMAT = .out

BLD_FULL_NAME = $(BLD_NAME)_v$(BLD_VERSION)_$(BLD_TYPE)_$(BLD_PLATFORM)$(BLD_FORMAT)

ROOTSOLVER_UNI_NAME = rootsolver.unitest
ROOTSOLVER_TESTS = rootsolver_unitest.txt
ROOTSOLVER_UNI_LOG = rootsolver_uni.log

#TODO: learn about g++ -M_ (something to do with headers, includes, makefiles e.t.c.)

all: main

MAIN_OBJECTS = main.o mainio.o rootsolver.o debug.o logger.o argparser.o utils.o
MAIN_ASSETS = rootsolver.conf
main: $(MAIN_OBJECTS)
	cp $(MAIN_ASSETS) $(BLD_FOLDER)
	$(CC) $(MAIN_OBJECTS) -o $(BLD_FOLDER)/$(BLD_FULL_NAME)

run:
	cd $(BLD_FOLDER) && exec ./$(BLD_FULL_NAME) $(ARGS)

TEST_OBJECTS = rootsolver_unitest.o rootsolver.o debug.o logger.o utils.o
TEST_ASSETS = rootsolver_unitest.txt
test: $(TEST_OBJECTS)
	cp $(TEST_ASSETS) $(TEST_FOLDER)
	$(CC) $(ARGS) $(TEST_OBJECTS) -o $(TEST_FOLDER)/$(ROOTSOLVER_UNI_NAME)
	cd $(TEST_FOLDER) && exec ./$(ROOTSOLVER_UNI_NAME) > $(ROOTSOLVER_UNI_LOG) 2>&1 < $(ROOTSOLVER_TESTS)

rootsolver_unitest.o:
	$(CC) $(CFLAGS) rootsolver_unitest.cpp

main.o:
	$(CC) $(CFLAGS) main.cpp

mainio.o:
	$(CC) $(CFLAGS) lib/util/mainio.cpp

rootsolver.o:
	$(CC) $(CFLAGS) lib/rootsolver.cpp

debug.o:
	$(CC) $(CFLAGS) lib/util/dbg/debug.cpp

logger.o:
	$(CC) $(CFLAGS) lib/util/dbg/logger.cpp

argparser.o:
	$(CC) $(CFLAGS) lib/util/argparser.cpp

utils.o:
	$(CC) $(CFLAGS) lib/util/utils.cpp

copy_main_assets:
	cp 

clean:
	rm -rf *.o

rmbld:
	cd $(BLD_FOLDER) && rm -rf *
	cd $(TEST_FOLDER) && rm -rf *