# CC is the compiler we are going to use
CC=gcc

# CFLAGS are the options we are going to pass
#	-c : compile
#	-Wall: gives simple warnings
CFLAGS= -c -Wall

# LINKLFAGS are the options used by th linker
# 	Only used by debug
LINKLFAGS=

# BIN is the binary directory
BIN= bin

all: clean 
all: compilador

debug: clean
debug: LINKLFAGS += -g
debug: CFLAGS += -g
debug: compilador

compilador: $(BIN)/main.o $(BIN)/lexical_analyser.o $(BIN)/state_machine.o
	$(CC) $(LINKLFAGS) $(BIN)/main.o $(BIN)/lexical_analyser.o $(BIN)/state_machine.o -o lexico

$(BIN)/main.o: main.c
	$(CC) $(CFLAGS) main.c -o $(BIN)/main.o

$(BIN)/lexical_analyser.o: lexical_analyser/lexical_analyser.c
	$(CC) $(CFLAGS) lexical_analyser/lexical_analyser.c -o $(BIN)/lexical_analyser.o

$(BIN)/state_machine.o: state_machine/state_machine.c
	$(CC) $(CFLAGS) state_machine/state_machine.c -o $(BIN)/state_machine.o

clean:
	rm -rf $(BIN)/*.o lexico