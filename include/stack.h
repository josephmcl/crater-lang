/*stack.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_STACK_H_
#define CRATER_LANG_STACK_H_

#include <stdlib.h>

typedef enum {
    GRAMMAR,
    INVARIANT_DEFS,
    INVARIANT_DEF,
    PRODUCTIONS,
    PRODUCTION,
    TOKEN
} pg_node_type;

typedef struct parser_grammar_s parser_grammar_t;
typedef struct invariant_defs_s invariant_defs_t;
typedef struct invariant_def_s invariant_def_t; 
typedef struct productions_s productions_t;
typedef struct production_s production_t;

struct production_s {
    lexical_store *children;
};

struct productions_s {
    production_t *children;
};

struct invariant_def_s {
    productions_t *children;
};

struct invariant_defs_s {
    invariant_def_t *children;
};

struct parser_grammar_s {
    invariant_defs_t *children;
};


// top 
//      : invariant_defs
// invariant_defs
//      : e
//      | invariant_defs invariant_def
// invariant_def 
//      : IDENTIFIER COLON tokens LINE_END productions SEMICOLON
// productions 
//      : empty
//      | productions production
// production
//      : LINE tokens LINE_END
// tokens
//      : empty
//      | tokens (*) # (*) = tokens besides LINE_END


typedef struct pg_node_u pg_node_t; 
struct pg_node_u {
    pg_node_type type;
    union _data {
        parser_grammar_t parser_grammar;
        invariant_defs_t invariant_defs;
        invariant_def_t invariant_def;
        productions_t productions;
        production_t production;
        lexical_store *leaf;
    } data;
};

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