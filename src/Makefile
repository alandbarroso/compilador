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

clean:
	rm -rf $(BIN)/*.o sintatico lexico compilador

all: clean
all: compilador

debug: clean
debug: LINKLFAGS += -g
debug: CFLAGS += -g
debug: compilador

compilador: $(BIN)/sintatico.o $(BIN)/pushdown_automata.o $(BIN)/lexical_analyser.o $(BIN)/state_machine.o $(BIN)/linked_list.o $(BIN)/keyword_analyser.o $(BIN)/symbol_table.o
	$(CC) $(LINKLFAGS) $? -o compilador

lexico: $(BIN)/lexico.o $(BIN)/lexical_analyser.o $(BIN)/state_machine.o $(BIN)/linked_list.o $(BIN)/keyword_analyser.o $(BIN)/symbol_table.o
	$(CC) $(LINKLFAGS) $? -o lexico

sintatico: $(BIN)/sintatico.o $(BIN)/syntax_analyser.o $(BIN)/pushdown_automata.o $(BIN)/lexical_analyser.o $(BIN)/state_machine.o $(BIN)/linked_list.o $(BIN)/keyword_analyser.o $(BIN)/symbol_table.o
	$(CC) $(LINKLFAGS) $? -o sintatico

$(BIN)/lexico.o: lexico.c
	$(CC) $(CFLAGS) $? -o $(BIN)/lexico.o

$(BIN)/sintatico.o: sintatico.c
	$(CC) $(CFLAGS) $? -o $(BIN)/sintatico.o

$(BIN)/syntax_analyser.o: syntax_analyser/syntax_analyser.c
	$(CC) $(CFLAGS) $? -o $(BIN)/syntax_analyser.o

$(BIN)/pushdown_automata.o: pushdown_automata/pushdown_automata.c
	$(CC) $(CFLAGS) $? -o $(BIN)/pushdown_automata.o

$(BIN)/lexical_analyser.o: lexical_analyser/lexical_analyser.c
	$(CC) $(CFLAGS) $? -o $(BIN)/lexical_analyser.o

$(BIN)/state_machine.o: state_machine/state_machine.c
	$(CC) $(CFLAGS) $? -o $(BIN)/state_machine.o

$(BIN)/linked_list.o: linked_list/linked_list.c
	$(CC) $(CFLAGS) $? -o $(BIN)/linked_list.o

$(BIN)/keyword_analyser.o: context_stack/keyword_analyser.c
	$(CC) $(CFLAGS) $? -o $(BIN)/keyword_analyser.o

$(BIN)/symbol_table.o: context_stack/symbol_table.c
	$(CC) $(CFLAGS) $? -o $(BIN)/symbol_table.o