/*stack.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_STACK_H_
#define CRATER_LANG_STACK_H_

#include <stdlib.h>

#include "pargen.h"

/* a stack for pointers to value types */
typedef struct {
    pg_node_t **content;
    unsigned int size;
    unsigned int capacity;
} stack_t;

stack_t stack_init();
void stack_free(stack_t *stack);

int stack_push(stack_t *stack, pg_node_t *item);
int stack_pop(stack_t *stack);
pg_node_t *stack_peek(stack_t *stack);

#endif