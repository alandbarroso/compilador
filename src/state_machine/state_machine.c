/*
 * state_machine.c
 *
 *  Created on: Sep 21, 2013
 *      Author: alan
 */
#include "state_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


StateMachine* initialize_state_machine(FILE* f)
{
	// Main vars
	int nb_states = 0;
	StateMachine* machine;

	int nb_accepting_states;
	int nb_ignoring_states;

	// Aux vars
	int i; // iterator
	int j; // iterator 2

	machine = (StateMachine*) malloc(sizeof(StateMachine));

	// First we read the number of states this machine is going to have
	fscanf(f, "%d", &nb_states);
	machine->n = nb_states;

	// We initialize the state array
	machine->states = (State*) malloc(nb_states * sizeof(State));
	for(i = 0; i < nb_states; i++)
	{
		State s;
		s.index = i;
		s.accepting = 0;
		s.ignoring = 0;

		s.name = (char*) malloc(sizeof(char));
		s.name[0] = '\0';

		machine->states[i] = s;
	}

	// We then get the accepting states and the names returned
	fscanf(f, "%d", &nb_accepting_states);
	for(i = 0; i < nb_accepting_states; i++)
	{
		int state_index;
		char state_name[128];

		// We read the state index and the name from the file
		fscanf(f, "%d %s", &state_index, state_name);

		machine->states[state_index].accepting = 1;
		machine->states[state_index].name = (char*) malloc((strlen(state_name) + 1)* sizeof(char));
		strcpy(machine->states[state_index].name, state_name);
	}

	// We try to get the ignoring states
	fscanf(f, "%d", &nb_ignoring_states);
	for(i = 0; i < nb_ignoring_states; i++)
	{
		int state_index;

		// We read the state index and the name from the file
		fscanf(f, "%d", &state_index);

		machine->states[state_index].ignoring = 1;
	}

	// Finally we get the transitions
	machine->transitions = (State***) malloc(machine->n * sizeof(State**));
	for(i = 0; i < machine->n; i++)
	{
		machine->transitions[i] = (State**) malloc(128 * sizeof(State*));
		// Chars on ascii table
		for(j = 0; j < 128; j++)
		{
			int result_state_index = -1;
			State* result_state;

			fscanf(f, "%d", &result_state_index);
			if(result_state_index == -1)
			{
				result_state = NULL;
			}
			else
			{
				result_state = &(machine->states[result_state_index]);
			}

			machine->transitions[i][j] = result_state;
		}
	}

	return machine;
}

State* get_initial_state(StateMachine* machine)
{
	return &(machine->states[0]);
}

State* get_next_state(StateMachine* machine, State* s, char c)
{
	int i = c;

	return machine->transitions[s->index][i];
}

void deleteStateMachine(StateMachine* machine)
{
	int i;

	// We free all arrays of the matrix
	for(i = 0; i < machine->n; i++)
	{
		free(machine->transitions[i]);
	}
	free(machine->transitions);

	// We free the machine
	free(machine);
}

void print_state_machine(StateMachine* machine)
{
	int i;

	for(i = 0; i < machine->n; i++)
	{
		int j;

		State* s = &(machine->states[i]);
		State* s1 = NULL;

		printf("State %d", i);

		if(machine->states[i].accepting)
		{
			printf(" -> accepting state! Returns %s", machine->states[i].name);
		}

		printf("\n");

		printf("Accepts transitions with: ");
		for(j = 0; j < 128; j++)
		{
			s1 = get_next_state(machine, s, j);

			if(s1 != NULL)
			{
				printf("%c", j);
			}
		}

		printf("\n");
	}
}
