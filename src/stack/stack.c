/*
 * stack.c
 *
 *  Created on: Oct 26, 2013
 *      Author: Kenji
 */
//==============================================================================
#include <stdio.h>  
#include <stdlib.h>
#include "stack.h"
//==============================================================================
pilha* criar (pilha p)
{
   p = NULL;
   
   return p;
 }
//==============================================================================
pilha* push (ElementType x,pilha p)
{
     pilha pont;
   if((pont = malloc(sizeof(tpont)))==NULL)
    printf("Memoria insulficiente\n");
   else{
    pont->info = x;
    pont->next = p;
   }
  return pont; 
}
//==============================================================================
void vazia (pilha p)
{
   if(p == NULL)
   printf("Pilha vazia\n");
   else
   printf("Pilha nao vazia\n");
}
//==============================================================================
void top (pilha p)
{
    if(p!=NULL) 
    printf("Topo da pilha %d",p->info);
    else
     printf("Pilha vazia\n");
}
//==============================================================================
pilha* pop(pilha p)
{
   tpont aux;
   
   if(p==NULL){
      printf("Nao ha elementos na pilha\n");            
     return;
   }  
   aux = p->next;
   free(p);
 
   return aux;
}
//==============================================================================
void imprimir(pilha p)
{
   tpont aux;
   
   if(p!= NULL)
   for(aux = p;aux!=NULL;aux=aux->next)
     printf("%d ",aux->info);
   else 
    printf("Pilha vazia\n");
}
