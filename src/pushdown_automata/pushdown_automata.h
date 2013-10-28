/*
*	pushdown_automata.h
*
* 	Created on: Oct 27, 2013
*		Author: alan
*/

#ifndef PUSHDOWN_AUTOMATA_H_
#define PUSHDOWN_AUTOMATA_H_

#include <stdio.h>

#include "../lexical_analyser/lexical_analyser.h"
#include "../linked_list/linked_list.h" 

/*
* ------------------------------------------------------
* Declarations
* ------------------------------------------------------
*/

/*
*	The state of the automata
*	int state_number: The number of the state in the atomata
*	int accepting: Indicates if the state is an accepting state
*	List* transitions: The list of transitions of the state
*	List* submachine_transition: The list of transitions that require calling a submachine
*/
typedef struct
{
	int state_number;
	int accepting;
	List* transitions;
	List* submachine_transitions;
} AutomataState;

/*
*	The Pushdown Automata
*	char* name: The name of the state
*	Automata_State** states: The list of states of the automata
*	int nb_states: The number of states in the automata
*/
typedef struct
{
	char* name;
	AutomataState** states;
	int nb_states;
} PushdownAutomata;

/*
*	The simple transition of the automata
*	Token token: The token to be received 
*	Automata_State state: The result state of the transition
*/
typedef struct
{
	Token* token;
	AutomataState* state;
} Transition;

/*
*	The submachine transition of the automata
*	Pushdown_Automata automata: The submachine to be called in the transition 
*	Automata_State state: The result state of the transition
*/
typedef struct
{
	PushdownAutomata* automata;
	AutomataState* state;
} SubmachineTransition;

/*
* ------------------------------------------------------
* Functions
* ------------------------------------------------------
*/

/*
*	Initialize an empty automata
*	char* name: The name of the new created automata
*/
PushdownAutomata* init_automata(char* name);

/*
*	Create the states and the transitions based on a file and the existing pushdown automatas
*	PushdownAutomata automata: The initialized atomata to be created
*	FILE* f: The file from wich the data will be extracted
*	PushdownAutomata** automatas: The other automatas
*	int nb_automatas: The total number of automatas
*/
void create_automata(PushdownAutomata* automata, FILE* f, PushdownAutomata** automatas, int nb_automatas);

/*
*	Deletes the automata
*	PushdownAutomata* automata: The automata to be deleted
*/
void delete_automata(PushdownAutomata* automata);

/*
*	Prints the automata
*	PushdownAutomata* automata: The automata to be printed
*/
void print_automata(PushdownAutomata* automata);

#endif /* PUSHDOWN_AUTOMATA_H_ */
