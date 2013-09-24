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

extern FILE* SOURCE_CODE;

extern int LINE;
extern int COLUMN;

extern char LAST_CHAR;
extern char CURRENT_CHAR;

extern int FILE_ENDED;

extern StateMachine* LEX_MACHINE;

typedef enum{
	INT,
	FLT,
	IDN,
	OPR,
	CHR,
	STR,
	ERR
} TokenClass;

typedef struct{
	TokenClass class; // Token class
	char* value; // Token value
	int line; // Line of the token
	int column; // Column of first token character
} Token;

/*
 * Initialize the LEX_MACHINE with the contents of the file 'lex_machine'
 * and reads the first char of the file f
 */
void init_lex(FILE *f);

/*
 * Return a token using the initialized files
 */
Token* get_token();

/*
 * Print the token
 */
void print_token(Token* t);

#endif /* LEXICAL_ANALYSER_H_ */
