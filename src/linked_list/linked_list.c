/*
 * linked_list.c
 *
 *  Created on: Sep 24, 2013
 *      Author: alan
 */
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

List* create_list(ElementType val, int (*equals_function)(ElementType, ElementType))
{
    List* list = (List*) malloc(sizeof(List));

    ListElement* element = (ListElement*) malloc(sizeof(ListElement)); 

    if(list == NULL || element == NULL)
    {
        printf("\n List creation failed \n");
        return NULL;
    }

    element->val = val;
    element->next = NULL;

    list->head = element;
    list->tail = element;
    list->equals = equals_function;

    return list;
}

void add_to_list(List* list, ElementType val)
{
    if(list == NULL)
    {
        printf("\n Node creation failed \n");
    }
    else
    {
        ListElement *element = (ListElement*) malloc(sizeof(ListElement));
        
        if(element == NULL)
        {
            printf("\n Node creation failed \n");
        }
        else
        {
            element->val = val;
            element->next = NULL;
        
            list->tail->next = element;
            list->tail = element;
        }
    }
}

ListElement* search_in_list(List* list, ElementType val)
{
    ListElement* element = list->head;

    while(element != NULL)
    {
        if( (*(list->equals))(val, element->val) )
        {
            return element;
        }

        element = element->next;
    }

    return NULL;
}

int eq(ElementType a, ElementType b)
{
    if(1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
