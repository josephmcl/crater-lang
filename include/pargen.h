/*pargen.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_PARGEN_H_
#define CRATER_LANG_PARGEN_H_

#include "lexer.h"

typedef enum {
    GRAMMAR,
    INVARIANT_DEFS,
    INVARIANT_DEF,
    PRODUCTIONS,
    PRODUCTION,
    TOKENS,
    TERMINAL
} pg_node_type;

typedef struct parser_grammar_s parser_grammar_t;
typedef struct invariant_defs_s invariant_defs_t;
typedef struct invariant_def_s invariant_def_t; 
typedef struct productions_s productions_t;
typedef struct production_s production_t;
typedef struct tokens_s tokens_t;

struct tokens_s {
    tokens_t *tokens;
    lexical_store *terminal;
};

struct production_s {
    lexical_store *T_LINE;
    tokens_t       *tokens;
    lexical_store *T_LINE_END;
};

struct productions_s {
    productions_t *productions;
    production_t *production;
};

struct invariant_def_s {
    lexical_store *T_IDENTIFIER;
    lexical_store *T_COLON;
    tokens_t      *tokens;
    lexical_store *T_LINE_END;
    productions_t *productions;

};

struct invariant_defs_s {
    invariant_defs_t *invariant_defs;
    invariant_def_t  *invariant_def;
};

struct parser_grammar_s {
    invariant_defs_t *invariant_def;
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
        parser_grammar_t *parser_grammar;
        invariant_defs_t *invariant_defs;
        invariant_def_t *invariant_def;
        productions_t *productions;
        production_t *production;
        tokens_t *tokens;
        lexical_store *terminal;
    } data;
};


#endif