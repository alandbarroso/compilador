/*
 * main.c
 *
 *  Created on: Sep 20, 2013
 *      Author: alan
 */
#include <stdio.h>
#include "state_machine/state_machine.h"

void test(FILE* f)
{
	char c;

	c = fgetc(f);

	printf("%c\n", c);
}


int main(int argc, char *argv[])
{
	FILE* f = fopen("lexical_analyser/lex_machine", "r");
	int i;

	for(i = 0; i < 6; i++)
	{
		test(f);
	}

	return 0;
}
