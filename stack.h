/*stack.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_STACK_H_
#define CRATER_LANG_STACK_H_

#include <stdlib.h>

/* unsafe stack, only push pointers to value types */
typedef struct {
    void *content;
    unsigned int size;
    unsigned int capacity;
} stack_t;

stack_t stack_init();
void stack_free(stack_t *stack);

int push(stack_t *stack, void *item);
int pop(stack_t *stack);
void *peek(stack_t *stack);

#endif