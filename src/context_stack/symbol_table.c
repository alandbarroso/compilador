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

/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

Scope* CURRENT_SCOPE;

/*
 * ------------------------------------------------------
 * Definitions
 * ------------------------------------------------------
 */

void init_var(){
	CURRENT_SCOPE = init_scope(NULL);

	CURRENT_SCOPE->number = 0;

	CURRENT_SCOPE->name = (char*) malloc((strlen("GLOBAL") + 1)*sizeof(char));
	strcpy(CURRENT_SCOPE->name, "GLOBAL");
}

ListElement* search_var(Scope* scope, char* idn)
{
	Symbol *symbol = init_symbol(idn);
	ListElement* element = NULL;

	if(scope != NULL)
	{
		element = search_in_list(scope->var_list, symbol);

		if(element == NULL)
		{
			element = search_var(scope->parent, symbol->id);
		}
	}

	return element;
}

Symbol* insert_var(char *idn)
{
	Symbol *symbol = init_symbol(idn);
	ListElement* element = search_var(CURRENT_SCOPE ,idn); 

	if(element == NULL)
	{
		add_to_list(CURRENT_SCOPE->var_list, symbol);

		return symbol;
	}
	else
	{
		free(symbol);

		return (Symbol*) element->val;
	}
}

Scope* init_scope(Scope* parent)
{
	Scope* s = (Scope*) malloc(sizeof(Scope));

	s->number = 0;
	s->var_list = create_list(&equals_var);
	s->parent = parent;
}

void print_list_vars(List* list)
{
    printf("\n -------Printing Var List ------- \n");
    if(list != NULL)
    {
        ListElement* element = list->head;
        while(element != NULL)
        {
            printf("\n [%s] - init:%d \n",((Symbol*) element->val)->id, ((Symbol*) element->val)->has_init);
            element = element->next;
        }
    }
    else
    {
        printf("\n Empty list!!! \n");
    }
    printf("\n -------Printing List End------- \n");

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

	s->type = NULL;

	s->has_init = 0;

	s->is_const = 0;

	s->is_type = 0;
	s->type_size = 0;

	s->is_struct = 0;
	
	s->child_scope = NULL;

	s->is_array = 0;

	s->is_function = NULL;
	s->param_list = NULL;
	s->size_of_vars = 0;

	s->ref_symbol = NULL;

	s->ref_name = NULL;

	s->size = 0;

	return s;
}