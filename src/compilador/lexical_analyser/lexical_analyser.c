/*
 * lexical_analyser.c
 *
 *  Created on: Sep 22, 2013
 *      Author: alan
 */
#include <stdlib.h>
#include <stdio.h>
#include "lexical_analyser.h"

void init_lex()
{
	FILE* f;

	f = fopen("lex_machine", "r");
	LEX_MACHINE = initialize_state_machine(f);
	fclose(f);

	LINE = 0;
	COLUMN = 0;

	LAST_READ_CHAR = fgetc(f);
}

Token get_token(FILE *f, StateMachine *lex_machine);
