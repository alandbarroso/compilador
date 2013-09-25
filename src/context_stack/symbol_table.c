/*
 *  var_analyser.c
 *
 *  Created on: Sep 24, 2013
 *      Author: Kenji
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../linked_list/linked_list.h"
#include "symbol_table.h"

/*
 * ------------------------------------------------------
 * Auxiliar Functions
 * ------------------------------------------------------
 */

 /*
	Returns:
		- 0: different
		- 1: equal

 */
int equals_var (ElementType e1, ElementType e2);

Symbol* init_symbol(char *idn);


/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

List* VARS_LIST;

/*
 * ------------------------------------------------------
 * Definitions
 * ------------------------------------------------------
 */

void init_var(){
	VARS_LIST = create_list(&equals_var);
}

int search_var(char* idn)
{
	Symbol *symbol = init_symbol(idn);

	if(search_in_list(VARS_LIST, symbol) == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void insert_var(char *idn)
{
	Symbol *symbol = init_symbol(idn);

	if(!search_var(idn))
	{
		add_to_list(VARS_LIST, symbol);
	}
	else
	{
		free(symbol);
	}
}

void print_list_vars(List* list)
{
    printf("\n -------Printing list Start------- \n");
    if(list != NULL)
    {
        ListElement* element = list->head;
        while(element != NULL)
        {
            printf("\n [%s] \n",((Symbol*) element->val)->id);
            element = element->next;
        }
    }
    else
    {
        printf("\n Empty list!!! \n");
    }
    printf("\n -------Printing list End------- \n");

    return;
}

int equals_var (ElementType e1, ElementType e2)
{
	Symbol *s1 = (Symbol*) e1;
	Symbol *s2 = (Symbol*) e2;

	if(!strcmp(s1->id, s2->id))
		return 1;
	
	return 0;
}

Symbol* init_symbol(char *idn)
{
	Symbol* s = (Symbol *) malloc(sizeof(Symbol));

	s->id = (char*) malloc((strlen(idn) + 1) * sizeof(char));
	strcpy(s->id, idn);

	s->value = 0;
	s->type = 0;

	return s;
}