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
 int equals_var (ElementType e1, ElementType e2){
 	if(!strcmp(e1.id, e2.id))
 		return 1;
 	
 	return 0;
 }


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
	VARS_LIST = NULL;
}

int search_var(char* idn)
{
	ElementType elemaux;

	elemaux.id = (char*) malloc((strlen(idn) + 1) * sizeof(char));
	strcpy(elemaux.id, idn);

	if(search_in_list(VARS_LIST, elemaux) == NULL)
	{
		free(elemaux.id);
		return 0;
	}
	else
	{
		free(elemaux.id);
		return 1;
	}
}

void insert_var(char *idn)
{
	ElementType elemaux;

	elemaux.id = (char*) malloc((strlen(idn) + 1) * sizeof(char));
	strcpy(elemaux.id, idn);

	if(VARS_LIST == NULL)
	{
		VARS_LIST = create_list(elemaux, &equals_var);
	} else
	{
		if(!search_var(idn))
		{
			add_to_list(VARS_LIST, elemaux);
		}
		else
		{
			free(elemaux.id);
		}
	}
}