/*
 * sintatico.c
 *
 *  Created on: Oct 27, 2013
 *      Author: alan
 */
#include <stdio.h>

#include "syntax_analyser/syntax_analyser.h"
#include "lexical_analyser/lexical_analyser.h"
#include "context_stack/keyword_analyser.h"
#include "context_stack/symbol_table.h"

int main(int argc, char *argv[])
{
	FILE* src_file = fopen("ENTRADA.TXT", "r");

	if(src_file != NULL)
	{
		// We start by initializing everything

		init_lex(src_file);

		init_var();

		init_keyword();

		init_syntax();

		// We the verify the syntax of the source code
		verify_syntax();
	}

	return 0;
}
