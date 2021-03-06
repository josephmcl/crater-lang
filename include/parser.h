/*parser.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_PARSER_H_
#define CRATER_LANG_PARSER_H_

#include "io.h"
#include "token.h"
#include "lexer.h"

typedef struct parser_info_s parser_info;
struct parser_info_s {
    int length;
    int capacity; 
};

struct parser {
    parser_info *info;
    int ( *generate) (void);
};

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



const extern struct parser Parser;

#endif