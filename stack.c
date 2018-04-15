/*stack.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */

#include "stack.h"

#define STACK_BLOCK 8

stack_t stack_init() {
    stack_t rv = {0};
    rv.content = calloc(0, sizeof(void *));
    return rv;
}
void stack_free(stack_t *stack) {
    free(stack->content);
    *stack = {0};
}

int push(void *item) {
    if (stack->size == stack->capacity) {
        stack->capacity += STACK_BLOCK;
        stack->content = realloc(stack->content, stack->capacity);
    }
    stack->content[stack->size] = item;
    stack->size += 1;
    return 0;
}
int pop(stack_t *stack) { 
    if (stack->size <= 0) 
        return 1;
    //TODO: in C99 I think we can use realloc to resize down
    // going to have to decide at some point...
    stack->size -= 1;
    stack->content[stack->size] = 0;
    
}
void *peek(stack_t *stack) {
    if (stack->size > 0)
        return stack->content[stack->size];
    return NULL;
}