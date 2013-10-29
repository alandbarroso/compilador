/*
 * syntax_analyser.c
 *
 *  Created on: Oct 29, 2013
 *      Author: alan
 */

#include <stdlib.h>
#include <stdio.h>

#include "syntax_analyser.h"

/*
 * ------------------------------------------------------
 * Auxiliar Functions
 * ------------------------------------------------------
 */



/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

const char* PROGRAMA_INIT = "initialization_files/DFAs/programa";
const char* PROGRAMA_NAME = "programa";

const char* COMANDO_INIT = "initialization_files/DFAs/comando";
const char* COMANDO_NAME = "comando";

const char* EXPRESSAO_INIT = "initialization_files/DFAs/expressao";
const char* EXPRESSAO_NAME = "expressao";

PushdownAutomata* INITIAL_SUBMACHINE;

PushdownAutomata** AUTOMATAS;

int NB_AUTOMATAS;

/*
 * ------------------------------------------------------
 * Definitions
 * ------------------------------------------------------
 */

void init_syntax()
{
	int NB_AUTOMATAS = 3;
	AUTOMATAS = (PushdownAutomata**) malloc(NB_AUTOMATAS*sizeof(PushdownAutomata*)); // The collection of automatas
	if(AUTOMATAS == NULL)
	{
		printf("Out of memory!\n");
		return;
	}

	AUTOMATAS[0] = init_automata(PROGRAMA_NAME);
	AUTOMATAS[1] = init_automata(COMANDO_NAME);
	AUTOMATAS[2] = init_automata(EXPRESSAO_NAME);

	FILE* f = fopen(PROGRAMA_INIT, "r"); // Initialization file for programa
	if (f != NULL)
	{
		create_automata(AUTOMATAS[0], f, AUTOMATAS, NB_AUTOMATAS);
	}
	fclose(f);
	
	f = fopen(COMANDO_INIT, "r"); // Initialization file for programa
	if (f != NULL)
	{
		create_automata(AUTOMATAS[1], f, AUTOMATAS, NB_AUTOMATAS);
	}
	fclose(f);

	f = fopen(EXPRESSAO_INIT, "r"); // Initialization file for programa
	if (f != NULL)
	{
		create_automata(AUTOMATAS[2], f, AUTOMATAS, NB_AUTOMATAS);
	}
	fclose(f);

	INITIAL_SUBMACHINE = AUTOMATAS[0];
}

void verify_syntax()
{
	Token** token = (Token**) malloc(sizeof(Token**)); // The token to be used
	int result; // The result sent from the machine

	*token = get_token();

	print_token((*token));

	result = recognize(INITIAL_SUBMACHINE, token);

	if(result) // Everything ok?
	{
		if((*token)->class == EOA)
		{
			printf("Source code correct!\n");
		}
		else
		{
			printf("Syntax error at line %d, column %d\n", (*token)->line, (*token)->column);
		}
	}
	else // Error somewhere!
	{
		if((*token)->class == ERR) // Lexic error!
		{
			printf("Lexical error line %d, column %d\n", (*token)->line, (*token)->column);
		}
		else // Syntax error!
		{
			printf("Syntax error at line %d, column %d\n", (*token)->line, (*token)->column);
		}
	}

	free(*token);
	free(token);
}

void delete_submachines()
{
	for(NB_AUTOMATAS = NB_AUTOMATAS - 1; NB_AUTOMATAS >= 0; NB_AUTOMATAS--)
	{
		delete_automata(AUTOMATAS[NB_AUTOMATAS]);
	}

	free(AUTOMATAS);
}