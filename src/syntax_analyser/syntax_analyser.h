/*
 * syntax_analyser.c
 *
 *  Created on: Oct 29, 2013
 *      Author: alan
 */

#ifndef SYNTAX_ANALYSER_H_
#define SYNTAX_ANALYSER_H_

#include <stdio.h>

#include "../pushdown_automata/pushdown_automata.h"

/*
 * ------------------------------------------------------
 * Variables
 * ------------------------------------------------------
 */

/*
*	Name of the submachines and files for each machine
*/
extern const char* PROGRAMA_INIT;
extern const char* PROGRAMA_NAME;

extern const char* COMANDO_INIT;
extern const char* COMANDO_NAME;

extern const char* EXPRESSAO_INIT;
extern const char* EXPRESSAO_NAME;

/*
*	The intial submachine
*/
extern PushdownAutomata* INITIAL_SUBMACHINE;

/*
*	The array of submachines
*/
extern PushdownAutomata** AUTOMATAS;

/*
*	The number of submachines
*/
extern int NB_AUTOMATAS;

/*
* ------------------------------------------------------
* Functions
* ------------------------------------------------------
*/

/*
*	Initialize each one of the automatas
*/
void init_syntax();

/*
*	Verify if the source has a correct syntax
*/
void verify_syntax();

/*
*	Empty the memory used by the machines
*/
void delete_submachines();

#endif /* SYNTAX_ANALYSER_H_ */