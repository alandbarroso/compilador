/*
*	semantic.h
*
* 	Created on: Nov 29, 2013
*		Author: alan
*/

#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "../linked_list/linked_list.h"
#include "../lexical_analyser/lexical_analyser.h"

extern List* MVN_PROGRAM;

extern const int MVN_WORD_SIZE;

typedef int (*semantic_function)(Token*);

void init_mvn_program();

semantic_function get_semantic_function(int function_number);

/* Function 1 */
int const_init(Token* token);

/* Function 2 */
int const_set_value(Token* token);

/* Function 3 */
int typedef_init(Token* token);

/* Function 4 */
int typedef_set_type(Token* token);

/* Function 5 */
int struct_init(Token* token);

/* Function 6 */
int set_type(Token* token);

/* Function 7 */
int create_var(Token* token);

/* Function 8 */
int set_as_array(Token* token);

/* Function 9 */
int struct_update_size(Token* token);

/* Function 10 */
int struct_end(Token* token);

/* Function 11 */
int var_end(Token* token);

/* Function 12 */
int function_init(Token* token);

#endif /* SEMANTIC_H_ */