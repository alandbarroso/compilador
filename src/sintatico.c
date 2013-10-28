/*
 * sintatico.c
 *
 *  Created on: Oct 27, 2013
 *      Author: alan
 */
#include <stdio.h>

#include "pushdown_automata/pushdown_automata.h"

const char* PROGRAMA_INIT = "initialization_files/DFAs/programa";
const char* PROGRAMA_NAME = "programa";

const char* COMANDO_INIT = "initialization_files/DFAs/comando";
const char* COMANDO_NAME = "comando";

const char* EXPRESSAO_INIT = "initialization_files/DFAs/expressao";
const char* EXPRESSAO_NAME = "expressao";

int main(int argc, char *argv[])
{
	int nb_automatas = 3;
	PushdownAutomata* automatas[nb_automatas]; // The collection of automatas

	automatas[0] = init_automata(PROGRAMA_NAME);
	automatas[1] = init_automata(COMANDO_NAME);
	automatas[2] = init_automata(EXPRESSAO_NAME);

	FILE* f = fopen(PROGRAMA_INIT, "r"); // Initialization file for programa
	if (f != NULL)
	{
		create_automata(automatas[0], f, automatas, nb_automatas);

		print_automata(automatas[0]);
	}
	fclose(f);
	
	f = fopen(COMANDO_INIT, "r"); // Initialization file for programa
	if (f != NULL)
	{
		create_automata(automatas[1], f, automatas, nb_automatas);

		print_automata(automatas[1]);
	}
	fclose(f);

	f = fopen(EXPRESSAO_INIT, "r"); // Initialization file for programa
	if (f != NULL)
	{
		create_automata(automatas[2], f, automatas, nb_automatas);

		print_automata(automatas[2]);
	}
	fclose(f);

	for(nb_automatas = nb_automatas - 1; nb_automatas >= 0; nb_automatas--)
	{
		delete_automata(automatas[nb_automatas]);
	}

	return 0;
}
