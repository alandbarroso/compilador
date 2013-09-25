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

extern List* VARS_LIST;

void init_var();

int search_var(char* idn);

void insert_var(char *idn);

#endif /* SYMBOL_TABLE_H_ */
