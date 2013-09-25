/*
 * linked_list.h
 *
 *  Created on: Sep 24, 2013
 *      Author: alan
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

 #include "../lexical_analyser/lexical_analyser.h"

typedef TokenClass Type;

typedef struct{
	char* id; 
	int value;
	Type type;
} ElementType;

typedef struct list_element
{
    ElementType val;
    struct list_element *next;
} ListElement;

typedef struct
{
    ListElement* head;
    ListElement* tail;

    int (*equals)(ElementType, ElementType);
} List;

List* create_list(ElementType val, int (*equals_function)(ElementType, ElementType));

void add_to_list(List* list, ElementType val);

ListElement* search_in_list(List* list, ElementType val);

void print_list(List* list);

int eq(ElementType a, ElementType b);

#endif /* LINKED_LIST_H_ */