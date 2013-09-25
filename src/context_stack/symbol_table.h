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

typedef TokenClass Type;

typedef struct{
	char* id;
	int value;
	Type type;
} Symbol;

extern List* VARS_LIST;

void init_var();

int search_var(char* idn);

void insert_var(char *idn);

void print_list_vars(List* list);

#endif /* SYMBOL_TABLE_H_ */
