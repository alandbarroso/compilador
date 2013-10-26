/*
 * stack.h
 *
 *  Created on: Oct 26, 2013
 *      Author: Kenji
 */

typedef void* ElementType;

typedef struct reg_pilha{
      ElementType info;
      struct reg_pilha *next ;
};

typedef struct reg_pilha *tpont;

typedef tpont pilha;


tpont* criar (pilha p);
tpont* push (ElementType x,pilha p);
void vazia (pilha p);
void top (pilha p);
tpont* pop(pilha p);
void imprimir(pilha p);
