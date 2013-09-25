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
 int equals_keyword (ElementType e1, ElementType e2){
 	char* s1 = (char*) e1;
 	char* s2 = (char*) e2;

 	if(!strcmp(s1, s2))
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
	char keyword_aux[32];

	init_file = fopen("context_stack/keywords", "r");

	
	KEYWORDS_LIST = NULL;

	while((fscanf(init_file, "%s", keyword_aux)) != EOF){
		char* keyword;

		// Populates the linked list
		keyword = (char*) malloc((strlen(keyword_aux) + 1) * sizeof(char));
		strcpy(keyword, keyword_aux);

		if(KEYWORDS_LIST==NULL){
			KEYWORDS_LIST = create_list(keyword, &equals_keyword);
		} else{
			add_to_list(KEYWORDS_LIST, keyword);
		}
	 }
	
	fclose(init_file);
}

int search_keyword(char* idn)
{
	if(search_in_list(KEYWORDS_LIST, idn) == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void print_list_keywords(List* list)
{
    printf("\n -------Printing list Start------- \n");
    if(list != NULL)
    {
        ListElement* element = list->head;
        while(element != NULL)
        {
            printf("\n [%s] \n",((char*) element->val));
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