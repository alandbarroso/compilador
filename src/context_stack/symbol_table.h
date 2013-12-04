/*
 *  symbol_table.h
 *
 *  Created on: Sep 24, 2013
 *      Author: Kenji
 */

#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include <stdio.h>
#include "../linked_list/linked_list.h"
#include "../lexical_analyser/lexical_analyser.h"

typedef TokenClass Type;

typedef struct Scope_
{
	char* name;
	int number;
	List* var_list;
	struct Scope_* parent;
} Scope;

typedef struct Symbol_
{
	char* id;
	char* type;

	int has_init;

	int is_const;

	int is_type;
	int type_size;

	int is_struct;

	Scope* child_scope;

	int is_array;

	void* is_function;
	List* param_list;
	int size_of_vars;

	struct Symbol_* ref_symbol;

	char* ref_name;

	int size;
} Symbol;

extern Scope* CURRENT_SCOPE;

void init_var();

ListElement* search_var(Scope* scope, char* idn);

Symbol* insert_var(char *idn);

Symbol* init_symbol(char *idn);

/* ------------------------------------------ */

Scope* init_scope(Scope* parent);

/* ------------------------------------------ */

void print_list_vars(List* list);

#endif /* SYMBOL_TABLE_H_ */
