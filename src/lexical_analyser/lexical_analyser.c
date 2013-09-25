/*
 * lexical_analyser.c
 *
 *  Created on: Sep 22, 2013
 *      Author: alan
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexical_analyser.h"
#include "../context_stack/keyword_analyser.h"
#include "../context_stack/symbol_table.h"

/*
 * ------------------------------------------------------
 * Auxiliar Functions
 * ------------------------------------------------------
 */

/*
 * Update the line and column
 */
void update_line_column();

/*
 * Get the class, based in the string returned
 */
TokenClass get_class(char* state_name, char* buffer);

/*
 * Append a char to a string
 */
void append_char(char** str, char c);

/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

FILE* SOURCE_CODE;

int LINE;
int COLUMN;

char LAST_CHAR = 0;
char CURRENT_CHAR = 0;

int FILE_ENDED = 0;

char CLASS_NAME[][4] = { "INT", "FLT", "IDN", "OPR", "CHR", "STR", "KEY", "VAR", "ERR" }; // Use the state name to determine the class
int NB_CLASS_NAME = 9; // The number of state names

StateMachine* LEX_MACHINE;

/*
 * ------------------------------------------------------
 * Definitions
 * ------------------------------------------------------
 */

void init_lex(FILE *f)
{
	FILE* init_file;

	init_file = fopen("lexical_analyser/lex_machine", "r");
	LEX_MACHINE = initialize_state_machine(init_file);
	fclose(init_file);

	LINE = 0;
	COLUMN = 0;

	SOURCE_CODE = f;
	CURRENT_CHAR = fgetc(SOURCE_CODE);

	FILE_ENDED = 0;

	init_keyword();

	init_var();

	print_list(KEYWORDS_LIST);

	printf("\n");
}

Token* get_token()
{
	Token* token;
	char* buffer;

	token = (Token*) malloc(sizeof(Token));

	buffer = (char*) malloc(sizeof(char));
	buffer[0] = '\0';

	// We start the machine
	State* current_state;
	State* next_state;
	current_state = NULL;
	next_state = get_initial_state(LEX_MACHINE);

	// We iterate while the next_state isn't NULL
	int token_noted = 0;
	while(next_state != NULL)
	{
		// We get the next state
		current_state = next_state;
		if(CURRENT_CHAR != EOF)
		{
			next_state = get_next_state(LEX_MACHINE, current_state, CURRENT_CHAR);
		}
		else
		{
			next_state = NULL;
		}

		// If the next state is NULL, the state machine has finished reading the string
		if(next_state != NULL)
		{
			// We write the contents on the buffer:
			// If it is in a ignoring state, ignore the buffer (commentary and blank characters
			if(!(next_state->ignoring))
			{
				// Append the char to the buffer
				append_char(&buffer, CURRENT_CHAR);

				// Write the first line and column of the token, if it wasn't
				if(!token_noted)
				{
					token->line = LINE;
					token->column = COLUMN;

					token_noted = 1;
				}
			}

			// We get the next char
			LAST_CHAR = CURRENT_CHAR;
			CURRENT_CHAR = fgetc(SOURCE_CODE);
			update_line_column();
		}
	}

	// We complete the token using the information from the state where we are
	if(current_state != NULL && !(current_state->ignoring)) // If the current state is not null and not a ignoring state
	{
		token->class = get_class(current_state->name, buffer);

		token->value = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(token->value, buffer);
	}
	else
	{
		if(CURRENT_CHAR == EOF)
		{
			FILE_ENDED = 1;

			token = NULL;
		}
		else
		{
			token->class = ERR;

			token->value = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(token->value, buffer);

			token->line = LINE;
			token->column = COLUMN;
		}
	}

	return token;
}

void print_token(Token* t)
{
	printf("Token\n");
	printf("Class: %s\n", CLASS_NAME[t->class]);
	printf("Value: %s\n", t->value);
	printf("Position: line %d, column %d\n", t->line, t->column);
}

void update_line_column()
{
	if(LAST_CHAR == '\n')
	{
		LINE++;
		COLUMN = 0;
	}
	else
	{
		COLUMN++;
	}
}

TokenClass get_class(char* state_name, char* buffer)
{
	TokenClass class = -1;
	int i;

	for(i = 0; i < NB_CLASS_NAME; i++)
	{
		if(!strcmp(CLASS_NAME[i], state_name))
		{
			class = i;
		}
	}

	if(class == -1)
	{
		class = ERR;
	}

	if(class == IDN)
	{

		if(search_keyword(buffer))
		{
			class = KEY;
		}
		else{
			class = VAR;

			insert_var(buffer);
		}
	}

	return class;
}

void append_char(char** str, char c)
{
	char* new_str = NULL;

	new_str = (char*) malloc((strlen(*str) + 2) * sizeof(char));
	strcpy(new_str, *str);
	new_str[strlen(*str)] = c;
	new_str[strlen(*str) + 1] = '\0';

	free(*str);

	*str = new_str;
}
