/*
 * main.c
 *
 *  Created on: Sep 20, 2013
 *      Author: alan
 */
#include <stdio.h>
#include "lexical_analyser/lexical_analyser.h"
#include "linked_list/linked_list.h"
#include "context_stack/keyword_analyser.h"
#include "context_stack/symbol_table.h"

int main(int argc, char *argv[])
{
	FILE* f = fopen("ENTRADA.TXT", "r");

	if(f != NULL)
	{
		init_lex(f);

		printf("LEX initialized!\n");

		Token* t;

		for(t = get_token(); t->class != EOA; t = get_token())
		{
			print_token(t);

			if(t->class == ERR)
			{
				printf("Lexical error at: line %d, column %d\n", t->line, t->column);
				printf("Exiting...\n");

				return 1;
			}
		}

		print_token(t);
	}
	else
	{
		printf("Error opening file!");
	}

	fclose(f);

	print_list_vars(VARS_LIST);

	printf("End of file\n");
	return 0;
}
