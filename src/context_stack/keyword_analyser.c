/*
 *  keyword_analyser.c
 *
 *  Created on: Sep 24, 2013
 *      Author: Kenji
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../linked_list/linked_list.h"
#include "keyword_analyser.h"

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
 int equals (ElementType e1, ElementType e2){
 	if(!strcmp(e1.id, e2.id))
 		return 1;
 	
 	return 0;
 }


/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

List* KEYWORDS_LIST;

/*
 * ------------------------------------------------------
 * Definitions
 * ------------------------------------------------------
 */

/*
 * Reads keywords file and populates linked list
 * 
 */
void init_keyword(){
	FILE* init_file;
	char keyword[32];

	init_file = fopen("context_stack/keywords", "r");

	
	KEYWORDS_LIST = NULL;

	while((fscanf(init_file, "%s", keyword)) != EOF){
		printf("%s\n", keyword);

		ElementType elemaux;

		// Populates the linked list
		elemaux.id = (char*) malloc((strlen(keyword) + 1) * sizeof(char));
		strcpy(elemaux.id, keyword);

		if(KEYWORDS_LIST==NULL){
			KEYWORDS_LIST = create_list(elemaux, &equals);
		} else{
			add_to_list(KEYWORDS_LIST, elemaux);
		}
	 }
	
	fclose(init_file);
}

int search_keyword(char* idn)
{
	ElementType elemaux;

	// Populates the linked list
	elemaux.id = (char*) malloc((strlen(idn) + 1) * sizeof(char));
	strcpy(elemaux.id, idn);

	if(search_in_list(KEYWORDS_LIST, elemaux) == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}