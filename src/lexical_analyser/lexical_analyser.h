/*
 * lexical_analyser.h
 *
 *  Created on: Sep 22, 2013
 *      Author: alan
 */

#ifndef LEXICAL_ANALYSER_H_
#define LEXICAL_ANALYSER_H_

#include <stdio.h>
#include "../state_machine/state_machine.h"

extern const char* LEX_INIT;

extern FILE* SOURCE_CODE; // Source to work

extern int LINE; // Current line read
extern int COLUMN; // Current column read

extern char LAST_CHAR; // Last char read
extern char CURRENT_CHAR; // Current char read

extern int FILE_ENDED; // Indicates if the file has finished

extern char CLASS_NAME[][4]; // Use the state name to determine the class
extern int NB_CLASS_NAME; // The number of state names

extern StateMachine* LEX_MACHINE; // The lex machine used

typedef enum{
	INT,
	FLT,
	IDN,
	OPR,
	CHR,
	STR,
	KEY,
	VAR,
	ERR,
	EOA
} TokenClass;

typedef char* TokenValue;

typedef struct{
	TokenClass class; // Token class
	TokenValue value; // Token value
	int line; // Line of the token
	int column; // Column of first token character
} Token;

/*
 * Initialize the LEX_MACHINE with the contents of the file 'lex_machine'
 * and reads the first char of the file
 */
void init_lex(FILE* source_file, char* init_file_name);

/*
 * Return a token using the initialized files
 */
Token* get_token();

/*
 * Print the token
 */
void print_token(Token* t);

#endif /* LEXICAL_ANALYSER_H_ */
