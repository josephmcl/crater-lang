/*stack.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */

#include <stdlib.h>

#include "stack.h"

/* unsafe stack, only push pointers to value types */
struct stack_s {
    void *content;
    unsigned int size;
    unsigned int capacity;
} stack_t;

stack_t stack_init();
void stack_free(stack_t *stack);

int stack_push(stack_t *stack, void *item);
int stack_pop(stack_t *stack);
void *stack_peek(stack_t *stack);