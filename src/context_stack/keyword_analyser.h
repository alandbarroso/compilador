/*
 *  keyword_analyser.h
 *
 *  Created on: Sep 24, 2013
 *      Author: Kenji
 */

#ifndef KEYWORD_ANALYSER_H_
#define KEYWORD_ANALYSER_H_

#include <stdio.h>
#include "../context_stack/linked_list.h"

extern List *keywords_list;

typedef enum{
	INT,
	FLT,
	CHR
} Type;


typedef struct{
	char* id; 
	int value;
	Type type; 
} ElementType;

#endif /* KEYWORD_ANALYSER_H_ */
