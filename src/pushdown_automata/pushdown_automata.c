/*
* pushdown_automata.c
*
*  Created on: Oct 27, 2013
*      Author: alan
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pushdown_automata.h"
#include "../linked_list/linked_list.h"

/*
* ------------------------------------------------------
* Auxiliar Functions
* ------------------------------------------------------
*/

/*
*	Always return 0 - Only implemented to init lists
*/
int equals_dummy(ElementType e1, ElementType e2);

/*
*	Initializate an automata state with the state number given
*/
AutomataState* init_automata_state(int state_number);

/*
*	Create token given class and value of the token
*/
Token* create_token(char* token_class, char* token_value);

/*
* ------------------------------------------------------
* Variables
* ------------------------------------------------------
*/


/*
* ------------------------------------------------------
* Definitions
* ------------------------------------------------------
*/

PushdownAutomata* init_automata(char* name)
{
	PushdownAutomata* automata;

	automata = (PushdownAutomata*) malloc(sizeof(PushdownAutomata));
	if(automata == NULL)
	{
		printf("Out of memory!\n");
		return NULL;
	}

	automata->name = name;
	automata->states = NULL;

	return automata;
}

void create_automata(PushdownAutomata* automata, FILE* f, PushdownAutomata** automatas, int nb_automatas)
{
	int nb_states; // The number of states in the automata

	int nb_accepting_states; // The number of accepting states in the machine
	int aux_accepting_state; // The number of the accepting state

	int nb_transitions; // The number of transitions in the file
	int aux_state; // The number of the origin state
	char aux_token_class[4]; // The class od the token read in the file
	char aux_token_value[256]; // The value of the token
	int aux_resulting_state; // The resulting state from the transistion

	Transition* aux_transition; // Auxliar to create normal transitions
	SubmachineTransition* aux_submachine_transition; // Auxiliar to create submachine transitions

	int i;

	fscanf(f, "%d", &nb_states);
	automata->nb_states = nb_states;

	automata->states = (AutomataState**) malloc(nb_states*sizeof(AutomataState*));
	if(automata->states == NULL)
	{
		printf("Out of memory\n");
		return;
	}

	for(nb_states = nb_states - 1; nb_states >= 0; nb_states--)
	{
		automata->states[nb_states] = init_automata_state(nb_states);
	}

	fscanf(f, "%d", &nb_accepting_states);
	for(; nb_accepting_states > 0; nb_accepting_states--)
	{
		fscanf(f, "%d", &aux_accepting_state);
		automata->states[aux_accepting_state]->accepting = 1;
	}

	fscanf(f, "%d", &nb_transitions);
	for(; nb_transitions > 0; nb_transitions--)
	{
		fscanf(f, "%d", &aux_state);
		fscanf(f, "%s", aux_token_class);
		fscanf(f, "%s", aux_token_value);
		fscanf(f, "%d", &aux_resulting_state);

		// We check if the token class equals a machine to be called
		if(!strcmp(aux_token_class, "MAC"))
		{
			for(i = 0; i < nb_automatas; i++)
			{
				if(!strcmp(aux_token_value, automatas[i]->name))
				{
					aux_submachine_transition = (SubmachineTransition*) malloc(sizeof(SubmachineTransition));
					if(aux_submachine_transition == NULL)
					{
						printf("Out of memory\n");
						return;
					}

					aux_submachine_transition->automata = automatas[i];
					aux_submachine_transition->state = automata->states[aux_resulting_state];

					add_to_list(automata->states[aux_state]->submachine_transitions, aux_submachine_transition);
				}
			}
		}
		// Else, is normal token transition
		else
		{
			aux_transition = (Transition*) malloc(sizeof(Transition));
			if(aux_transition == NULL)
			{
				printf("Out of memory\n");
				return;
			}

			aux_transition->token = create_token(aux_token_class, aux_token_value);
			aux_transition->state = automata->states[aux_resulting_state];
			
			add_to_list(automata->states[aux_state]->transitions, aux_transition);
		}
	}
}

void delete_automata(PushdownAutomata* automata)
{
	int i;

	for(i = 0; i < automata->nb_states; i++)
	{
		delete_list(automata->states[i]->transitions);
		delete_list(automata->states[i]->submachine_transitions);

		free(automata->states[i]);
	}

	free(automata);
}

void print_automata(PushdownAutomata* automata)
{
	int i;
	ListElement* element;

	Transition* t;
	SubmachineTransition* st;

	printf("-------------------------------\n");
	printf("Automata %s:\n", automata->name);
	printf("Number of states %d\n", automata->nb_states);
	for(i = 0; i < automata->nb_states; i++)
	{
		printf("--------------\n");
		printf("State %d: %s\n", automata->states[i]->state_number, (automata->states[i]->accepting) ? "Accepting" : "Normal");

		element = automata->states[i]->transitions->head;
		while(element != NULL)
		{
			t = (Transition*) element-> val;

			printf("If %s %s - To %d\n", CLASS_NAME[t->token->class], t->token->value, t->state->state_number);
			element = element->next;
		}

		element = automata->states[i]->submachine_transitions->head;
		while(element != NULL)
		{
			st = (SubmachineTransition*) element-> val;

			printf("If machine %s - To %d\n", st->automata->name, st->state->state_number);
			element = element->next;
		}
	}
	printf("--------------\n");
	printf("End of automata %s\n", automata->name);
	printf("-------------------------------\n\n");
}

int equals_dummy(ElementType e1, ElementType e2)
{
	return 0;
}

AutomataState* init_automata_state(int state_number)
{
	AutomataState* state;

	state = (AutomataState*) malloc(sizeof(AutomataState));
	if(state == NULL)
	{
		printf("Out of memory!\n");
		return NULL;
	}

	state->state_number = state_number;
	state->accepting = 0;
	state->transitions = create_list(&equals_dummy);
	state->submachine_transitions = create_list(&equals_dummy);

	return state;
}

Token* create_token(char* token_class, char* token_value)
{
	Token* token = (Token*) malloc(sizeof(Token));
	if(token == NULL)
	{
		printf("Out of memory\n");
		return NULL;
	}

	token->class = -1;
	int i;

	for(i = 0; i < NB_CLASS_NAME; i++)
	{
		if(!strcmp(CLASS_NAME[i], token_class))
		{
			token->class = i;
		}
	}

	if(token->class == -1)
	{
		token->class = ERR;
	}

	if(!strcmp(token_value, "NULL"))
	{
		token->value = NULL;
	}
	else
	{
		token->value = (char*) malloc((strlen(token_value) + 1) * sizeof(char));
		strcpy(token->value, token_value);
	}

	return token;
}