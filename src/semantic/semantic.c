/*
*	semantic.c
*
* 	Created on: Nov 29, 2013
*		Author: alan
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "semantic.h"
#include "mvn_command.h"
#include "../lexical_analyser/lexical_analyser.h"
#include "../syntax_analyser/syntax_analyser.h"
#include "../context_stack/symbol_table.h"

List* MVN_PROGRAM;

const int MVN_WORD_SIZE = 2;

Symbol* AUX;

Symbol* STRUCT_AUX;

Symbol* FUNCTION_AUX;

char* TYPE_AUX;
int TYPE_SIZE_AUX;
Symbol* REF_SYMBOL_AUX;

/* ------------------------------------------------------------------------------------------------- */

/*
*	Semantic function to be done
*/
int semantico_tdb(Token* token);

char get_char_from_string(char* str);

/* ------------------------------------------------------------------------------------------------- */

void init_mvn_program()
{
	MVN_PROGRAM = create_list(&equals_mvn_command);

	add_to_list(MVN_PROGRAM, init_command("EMPILHA", EP, " ")); 
	add_to_list(MVN_PROGRAM, init_command("END_INICIAL", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("TAMANHO", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("DESEMPILHA", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("COPIA_BLOCO", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("END_BLOCO_ORIGEM", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("END_BLOCO_ALVO", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("TAMANHO_BLOCO", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("ACESSA", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("END_ORIGEM", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("GRAVA", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("VALOR", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("END_ALVO", EP, "")); 
	add_to_list(MVN_PROGRAM, init_command("TOPO", EP, ""));
	add_to_list(MVN_PROGRAM, init_command("", ORG, "/000")); 
	add_to_list(MVN_PROGRAM, init_command("", JP, "MAIN"));

	add_to_list(MVN_PROGRAM, init_command("AUX_RETURN", K, "/0000"));
}

semantic_function get_semantic_function(int function_number)
{
	semantic_function f;

	switch(function_number)
	{
		case 0:
			f = &semantico_tdb;
			break;
		case 1:
			f = &const_init;
			break;
		case 2:
			f = &const_set_value;
			break;
		case 3:
			f = &typedef_init;
			break;
		case 4:
			f = &typedef_set_type;
			break;
		case 5:
			f = &struct_init;
			break;
		case 6:
			f = &set_type;
			break;
		case 7:
			f = &create_var;
			break;
		case 8:
			f = &set_as_array;
			break;
		case 9:
			f = &struct_update_size;
			break;
		case 10:
			f = &struct_end;
			break;
		case 11:
			f = &var_end;
			break;
		case 12:
			f = &function_init;
			break;
		default:
			f = &semantico_tdb;
			break;
	}

	return f;
}

int const_init(Token* token)
{
	AUX = (Symbol *) token->value;

	// The symbol has been initiated
	AUX->has_init = 1;

	// Set the variable as constant
	AUX->is_const = 1;
	
	// Set the name to be used on the mvn program
	AUX->ref_name = (char *) malloc((strlen("CONST_") + strlen(AUX->id) + 1)*sizeof(char));
	strcpy(AUX->ref_name, "CONST_");
	strcat(AUX->ref_name, AUX->id);

	return 1;
}

int const_set_value(Token* token)
{
	char* value;

	switch(token->class)
	{
		case INT:
			AUX->type = malloc((strlen("int") + 1)*sizeof(char));
			strcpy(AUX->type, "int");

			value = malloc(1 + (strlen(token->value) + 1)*sizeof(char));
			strcpy(value, "=");
			strcat(value, token->value);
			break;
		case FLT:
			AUX->type = malloc((strlen("float") + 1)*sizeof(char));
			strcpy(AUX->type, "float");

			value = malloc((strlen("/0000") + 1)*sizeof(char));
			strcpy(value, "/0000");
			break;
		case CHR:
			AUX->type = malloc((strlen("char") + 1)*sizeof(char));
			strcpy(AUX->type, "char");

			value = malloc((strlen("=128") + 1)*sizeof(char));
			sprintf(value, "=%d", get_char_from_string(token->value));
			break;
		case KEY:
			AUX->type = malloc((strlen("bool") + 1)*sizeof(char));
			strcpy(AUX->type, "bool");

			if(!strcmp(token->value, "true"))
			{
				value = malloc((strlen("/0001") + 1)*sizeof(char));
				strcpy(value, "/0001");
			}
			else
			{
				value = malloc((strlen("/0000") + 1)*sizeof(char));
				strcpy(value, "/0000");
			}

			break;
	}

	AUX->size = 1;

	add_to_list(MVN_PROGRAM, init_command(AUX->ref_name, K, value));
	free(value);

	return 1;
}

int typedef_init(Token* token)
{
	AUX = (Symbol *) token->value;

	if(AUX->has_init)
	{
		printf("Error!\n");
		printf("Error: %s cannot be a type, has already been defined\n", AUX->id);
		return 0;
	}

	AUX->is_type = 1;

	AUX->has_init = 1;

	return 1;
}

int typedef_set_type(Token* token)
{
	Symbol* s;

	switch(token->class)
	{
		case KEY:
			AUX->type = malloc((strlen(token->value) + 1)*sizeof(char));
			strcpy(AUX->type, token->value);

			AUX->type_size = 1;

			break;
		case VAR:
			s = (Symbol *) token->value;
			if(s->has_init && s->is_type)
			{
				AUX->type = malloc((strlen(s->type) + 1)*sizeof(char));
				strcpy(AUX->type, s->type);

				AUX->type_size = s->type_size;
			}
			else
			{
				printf("Error!\n");
				if(!s->has_init)
				{
					printf("Error: %s has not been initialized.\n", s->id);
				}
				else
				{
					printf("Error: %s is not a valid type.\n", s->id);
				}
				return 0;
			}
			break;
	}

	return 1;
}

int struct_init(Token* token)
{
	STRUCT_AUX = (Symbol *) token->value;

	if(STRUCT_AUX->has_init)
	{
		printf("Error!\n");
		printf("Error: %s already defined, cannot be a struct type.\n", STRUCT_AUX->id);
	}

	STRUCT_AUX->has_init = 1;

	STRUCT_AUX->is_type = 1;
	STRUCT_AUX->type = malloc((strlen(STRUCT_AUX->id) + 1)*sizeof(char));
	strcpy(STRUCT_AUX->type, STRUCT_AUX->id);

	STRUCT_AUX->is_struct = 1;

	STRUCT_AUX->child_scope = init_scope(CURRENT_SCOPE);
	CURRENT_SCOPE = STRUCT_AUX->child_scope;

	CURRENT_SCOPE->name = (char*) malloc((strlen(STRUCT_AUX->id) + 1)*sizeof(char));
	strcpy(CURRENT_SCOPE->name, STRUCT_AUX->id);

	STRUCT_AUX->type_size = 0;

	return 1;
}

int set_type(Token* token)
{
	Symbol* s;

	switch(token->class)
	{
		case KEY:
			TYPE_AUX = malloc((strlen(token->value) + 1)*sizeof(char));
			strcpy(TYPE_AUX, token->value);

			if(strcmp(token->value, "void"))
			{
				TYPE_SIZE_AUX = 1;
			}
			else
			{
				TYPE_SIZE_AUX = 0;	
			}

			REF_SYMBOL_AUX = NULL;

			break;
		case VAR:
			s = (Symbol *) token->value;
			if(s->has_init && s->is_type)
			{
				TYPE_AUX = malloc((strlen(s->type) + 1)*sizeof(char));
				strcpy(TYPE_AUX, s->type);

				TYPE_SIZE_AUX = s->type_size;

				REF_SYMBOL_AUX = s;
			}
			else
			{
				printf("Error!\n");
				if(!s->has_init)
				{
					printf("Error: %s has not been initialized.\n", s->id);
				}
				else
				{
					printf("Error: %s is not a valid type.\n", s->id);
				}
				return 0;
			}
			break;
	}

	return 1;
}

int create_var(Token* token)
{
	AUX = (Symbol *) token->value;

	if(AUX->is_type)
	{
		printf("Error!\n");
		printf("Error: %s is a type.\n", AUX->id);

		return 0;
	}

	// We check if the given symbol is in the current scope or not
	if(search_in_list(CURRENT_SCOPE->var_list, AUX) == NULL)
	{
		// It's not, we must insert the variable in the scope
		AUX = init_symbol(AUX->id);
		add_to_list(CURRENT_SCOPE->var_list, AUX);
	}

	if(AUX->has_init)
	{
		printf("Error!\n");
		printf("Error: double definition of %s.\n", AUX->id);
		return 0;
	}

	AUX->has_init = 1;

	AUX->type = TYPE_AUX;
	AUX->size = TYPE_SIZE_AUX;
	AUX->ref_symbol = REF_SYMBOL_AUX;

	return 1;
}

int set_as_array(Token* token)
{
	int	array_size;

	array_size = atoi(token->value);

	AUX->is_array = 1;
	AUX->size = array_size*AUX->size;

	return 1;
}

int struct_update_size(Token* token)
{
	STRUCT_AUX->type_size += AUX->size;
}

int struct_end(Token* token)
{
	Scope* scope;

	scope = CURRENT_SCOPE;

	while(scope != NULL)
	{
		print_list_vars(scope->var_list);

		scope = scope->parent;
	}

	printf("Size of %s: %d\n", STRUCT_AUX->id, STRUCT_AUX->type_size);

	// We go to the parent scope
	CURRENT_SCOPE = CURRENT_SCOPE->parent;

	return 1;
}

int var_end(Token* token)
{
	char size[50];

	AUX->ref_name = (char*) malloc((strlen(CURRENT_SCOPE->name) + 1 + strlen(AUX->id) + 1)*sizeof(char));
	strcpy(AUX->ref_name, CURRENT_SCOPE->name);
	strcat(AUX->ref_name, "_");
	strcat(AUX->ref_name, AUX->id);

	sprintf(size, "=%d", AUX->size);

	add_to_list(MVN_PROGRAM, init_command(AUX->ref_name, BM, size));

	return 1;
}

int function_init(Token* token)
{
	FUNCTION_AUX = (Symbol*) token->value;

	if(AUX->is_type)
	{
		printf("Error!\n");
		printf("Error: %s is a type.\n", AUX->id);

		return 0;
	}

	if(AUX->has_init)
	{
		printf("Error!\n");
		printf("Error: double definition of %s.\n", AUX->id);
		return 0;
	}

	FUNCTION_AUX->has_init = 1;
	FUNCTION_AUX->is_function = 1;

	FUNCTION_AUX->type = TYPE_AUX;
	FUNCTION_AUX->size = TYPE_SIZE_AUX;
	FUNCTION_AUX->ref_symbol = REF_SYMBOL_AUX;

	FUNCTION_AUX->param_list = create_list(NULL);

	FUNCTION_AUX->size_of_vars = 0;

	FUNCTION_AUX->child_scope = init_scope(CURRENT_SCOPE);
	CURRENT_SCOPE = FUNCTION_AUX->child_scope;

	CURRENT_SCOPE->name = (char*) malloc((strlen(FUNCTION_AUX->id) + 1)*sizeof(char));
	strcpy(CURRENT_SCOPE->name, FUNCTION_AUX->id);

	return 1;
}

/* ------------------------------------------------------------------------------------------------- */

int semantico_tdb(Token* token)
{
	printf("TODO\n");

	return 1;
}

char get_char_from_string(char* str)
{
	char c;

	if(!strcmp(str, "'\\0'"))
		return '\0';
	if(!strcmp(str, "'\\t'"))
		return '\t';
	if(!strcmp(str, "'\\n'"))
		return '\n';
	if(!strcmp(str, "'\\t'"))
		return '\t';
	if(!strcmp(str, "'\\r'"))
		return '\r';
	if(!strcmp(str, "'\\''"))
		return '\'';

	sscanf(str, "'%c'", &c);

	return c;
}