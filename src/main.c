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
	FILE* f = fopen("src_file", "r");

	if(f != NULL)
	{
		init_lex(f);

		printf("LEX initialized!\n");

		while(!FILE_ENDED)
		{
			Token* t;

			t = get_token();

			if(t->class != EOA)
			{
				print_token(t);

				if(t->class == ERR)
				{
					printf("Lexical error at: line %d, column %d\n", t->line, t->column);
					printf("Exiting...\n");

					return 1;
				}
			}
			else
			{
				print_token(t);
				
				printf("End of file\n");

				print_list(VARS_LIST);
				
				return 0;
			}
		}
	}
	else
	{
		printf("Error opening file!");
	}

	fclose(f);

	printf("End of file\n");
	return 0;
}
