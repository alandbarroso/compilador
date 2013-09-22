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

int LINE;
int COLUMN;

char LAST_READ_CHAR;

StateMachine* LEX_MACHINE;

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
 * and reads the first char
 */
void init_lex();

Token get_token(FILE *f, StateMachine *lex_machine);

#endif /* LEXICAL_ANALYSER_H_ */
