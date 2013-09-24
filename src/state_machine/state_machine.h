/*
 * state_machine.h
 *
 *  Created on: Sep 20, 2013
 *      Author: alan
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdio.h>

typedef struct
{
	int index; // Index of the state machine
	int accepting; // Indicates if it is an accepting state
	int ignoring; // Indicates if the contents of this states should be recorded
	char* name; // Only if accepting state
} State;

typedef struct
{
	int n; // Number of states
	State* states; // List of states
	State*** transitions; // List of transitions
} StateMachine;

/*
 * Initializes the state machine using a file containing:
 *
 * n - number of states
 * m - number of accepting states
 * m lines of:
 * 	k TOKEN - k is the number of the state and TOKEN is the string containing the TOKEN type returned by the state
 * n lines of:
 * 	The matrix with the transitions
 *
 * -1 indicates the exit state(stops the transitions)
 */
StateMachine* initialize_state_machine(FILE* f);

/*
 * Returns the initial state of the state machine
 */
State* get_initial_state(StateMachine* machine);

/*
 * Returns the next state of the machine
 * 	s - The current state
 * 	c - The transition char
 */
State* get_next_state(StateMachine* machine, State* s, char c);

/*
 * Deletes the state machine, freeing the memory
 */
void deleteStateMachine(StateMachine* machine);

/*
 * Print the state machine states and transactions
 */
void print_state_machine(StateMachine* machine);

#endif /* STATE_MACHINE_H_ */
