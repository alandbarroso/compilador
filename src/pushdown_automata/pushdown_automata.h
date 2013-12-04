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
*	The transition of the automata
*	void* transition_value: The value used to compare if the transition can occour 
*	Automata_State next_state: The result state of the transition
*/
typedef struct
{
	void* transition_value;
	AutomataState* next_state;
	int (*semantic_action)(Token*);
} Transition;

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
*	Recognizes a language using an automata. If the text belongs to the language, return true, false if not
*	PushdownAutomata* automata: The automata used to reconize.
*	Token** token: The last token read by the lexical analyser
*/
int recognize(PushdownAutomata* automata, Token** token);

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
