/*
 * linked_list.c
 *
 *  Created on: Sep 24, 2013
 *      Author: alan
 */
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

List* create_list(int (*equals_function)(ElementType, ElementType))
{
    List* list = (List*) malloc(sizeof(List));

    if(list == NULL)
    {
        printf("\n List creation failed \n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
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
            
            if(list->head == NULL)
            {
                list->head = element;
                list->tail = element;
            }
            else
            {
                list->tail->next = element;
                list->tail = element;
            }
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

void delete_list(List* list)
{
    ListElement* element = list->head;
    ListElement* element_aux = element;

    while(element_aux != NULL)
    {
        element = element_aux;

        free(element->val);
        element_aux = element->next;
        free(element);
    }

    free(list);
}