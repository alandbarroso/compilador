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
*	Semantic function to be done
*/
void semantico_tdb();

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
					aux_transition = (Transition*) malloc(sizeof(Transition));
					if(aux_transition == NULL)
					{
						printf("Out of memory\n");
						return;
					}

					aux_transition->transition_value = automatas[i];
					aux_transition->next_state = automata->states[aux_resulting_state];
					aux_transition->semantic_action = &semantico_tdb;

					add_to_list(automata->states[aux_state]->submachine_transitions, aux_transition);
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

			aux_transition->transition_value = create_token(aux_token_class, aux_token_value);
			aux_transition->next_state = automata->states[aux_resulting_state];
			aux_transition->semantic_action = &semantico_tdb;
			
			add_to_list(automata->states[aux_state]->transitions, aux_transition);
		}
	}
}

int recognize(PushdownAutomata* automata, Token** token)
{
	AutomataState* current_state = automata->states[0]; // The current state of the machine
	AutomataState* next_state; // The next state of the automata

	int finished_automata = 0; // Indicates if there is no more transitions to be made

	ListElement* element;
	Transition* t; // Auxiliar to the transitions

	Token* transition_token; // The token used on the transition 
	PushdownAutomata* transition_automata; // The auxiliar automata used on a transition

	int result = 1; // The final result of the automata 

	printf("-------------------------------------------------------\n");
	printf("Started machine %s\n", automata->name);
	printf("\n");

	while((*token)->class != EOA && !finished_automata)
	{
		next_state = NULL; // Restart the transitions

		// First we try using a token transition
		element = current_state->transitions->head;
		while(next_state == NULL && element != NULL)
		{
			t = (Transition*) element->val;

			transition_token = (Token*) t->transition_value;

			if(transition_token->class == (*token)->class)
			{
				// If no value is specified, we always get the next state
				if(transition_token->value == NULL)
				{
					next_state = t->next_state;

					printf("-----------------------------------\n");
					printf("Transited from %d to %d using the token!\n", current_state->state_number, next_state->state_number);
					printf("\n");

					printf("Semantic action:\n");
					(*(t->semantic_action))();
					printf("\n");
				}
				else // Else, we compare the values
				{
					if(!strcmp(transition_token->value, (*token)->value))
					{
						next_state = t->next_state;

						printf("-----------------------------------\n");
						printf("Transited from %d to %d using the token!\n", current_state->state_number, next_state->state_number);
						printf("\n");

						printf("Semantic action:\n");
						(*(t->semantic_action))();
						printf("\n");
					}
				}
			}
			
			element = element->next;
		}

		// If no state was transited from the token transitions, we try the machine transitions
		if(next_state == NULL)
		{
			element = current_state->submachine_transitions->head;
			while(next_state == NULL && element != NULL)
			{
				t = (Transition*) element->val;

				transition_automata = (PushdownAutomata*) t->transition_value;

				// If the submachine recognizes the transition, we go to the nex state
				if(recognize(transition_automata, token))
				{
					next_state = t->next_state;

					printf("-----------------------------------\n");
					printf("Transited from %d to %d using the machine %s!\n", current_state->state_number, next_state->state_number, transition_automata->name);
					printf("\n");

					printf("Semantic action:\n");
					(*(t->semantic_action))();
					printf("\n");
				}
				
				element = element->next;
			}

			if(next_state == NULL) // All the possibilities were checked, automata has ended
			{
				finished_automata = 1;
			}
			else // We found a transition via Submachine
			{
				current_state = next_state;
			}
		}
		else // Transition occourred via token, need to get a new one
		{
			current_state = next_state;

			// We free the last token
			free(*token);

			// And get a new one
			*token = get_token();

			print_token((*token));

			// Small check if the given token have an error
			if((*token)->class == ERR)
			{
				return 0; // We return a error => We could not recognize the file
			}
		}
	}
	printf("-----------------------------------\n\n");

	// We finally verify if the the last state to see if the we have accepted the language or not
	if(current_state->accepting)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	printf("-------------------------------------------------------\n");

	return result;
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

	Token* token;
	PushdownAutomata* aux_automata;

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
			t = (Transition*) element->val;

			token = (Token*) t->transition_value;

			printf("If %s %s - To %d\n", CLASS_NAME[token->class], token->value, t->next_state->state_number);
			element = element->next;
		}

		element = automata->states[i]->submachine_transitions->head;
		while(element != NULL)
		{
			t = (Transition*) element->val;

			aux_automata = (PushdownAutomata*) t->transition_value;

			printf("If machine %s - To %d\n", aux_automata->name, t->next_state->state_number);
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

void semantico_tdb()
{
	printf("TODO\n");
}