/*
 *  keyword_analyser.h
 *
 *  Created on: Sep 24, 2013
 *      Author: Kenji
 */

#ifndef KEYWORD_ANALYSER_H_
#define KEYWORD_ANALYSER_H_

#include <stdio.h>
#include "../linked_list/linked_list.h"

extern const char* KEY_INIT;

extern List* KEYWORDS_LIST;

void init_keyword();

int search_keyword(char* idn);

void print_list_keywords(List* list);

#endif /* KEYWORD_ANALYSER_H_ */
