/*
 *  keyword_analyser.c
 *
 *  Created on: Sep 24, 2013
 *      Author: Kenji
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
 		return 0;
 	if(e1.value != e2.value)
 		return 0;
 	if(e1.type != e2.type)
 		return 0;
 	return 1;
 }

/*
 * Update the line and column
 */


/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

List *keywords_list;

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

	init_file = fopen("keywords", "r");

	
	keywords_list = NULL;

	while((fscanf(init_file, "%s", keyword)) != EOF){
		printf("%s\n", keyword);

		ElementType elemaux;

		// Populates the linked list
		elemaux->id = (char*) malloc((strlen(keyword) + 1) * sizeof(char));
		strcpy(elemaux->id, keyword);

		if(keywords_list==NULL){
			keywords_list = createlist(elemaux, &equals);
		} else{
			add_to_list(keywords_list, elemaux);
		}
	 }
	
	fclose(init_file);
}