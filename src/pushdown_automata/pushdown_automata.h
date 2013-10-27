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
	List* submachine_transition;
} AutomataState;

/*
*	The Pushdown Automata
*	char* name: The name of the state
*	Automata_State* states: The list of states of the automata
*/
typedef struct
{
	char* name;
	AutomataState* state;
} PushdownAutomata;

/*
*	The simple transition of the automata
*	TokenClass token_class: If submachine_transition equals false, this is the class of tokens acepted by the trasition
*	char* value: If the transition requires a precise value, it contains the value required. Null if not
*	Automata_State state: The result state of the transition
*/
typedef struct
{
	TokenClass token_class;
	TokenValue value;
	AutomataState* state;
} Transition;

/*
*	The submachine transition of the automata
*	Pushdown_Automata automata: The submachine to be called in the transition 
*	Automata_State state: The result state of the transition
*/
typedef struct
{
	PushdownAutomata automata;
	Automata_State* state;
} SubmachineTransition;

#endif /* PUSHDOWN_AUTOMATA_H_ */
