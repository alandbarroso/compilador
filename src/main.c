/*
 * main.c
 *
 *  Created on: Sep 20, 2013
 *      Author: alan
 */
#include <stdio.h>
#include "lexical_analyser/lexical_analyser.h"

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

			if(t != NULL)
			{
				printf("-------------------------------\n");
				print_token(t);
				printf("-------------------------------\n\n");

				if(t->class == ERR)
				{
					printf("Lexical error at: line %d, column %d\n", t->line, t->column);
					printf("Exiting...\n");

					return 1;
				}
			}
			else
			{
				printf("End of file\n");

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