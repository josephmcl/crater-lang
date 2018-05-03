/*parser.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "io.h"
#include "token.h"
#include "lexer.h"


typedef struct production_s production;
struct production_s {
    int index;
    uint8_t *name;
};

typedef struct parser_info_s parser_info;
struct parser_info_s {
    int count;
};

typedef production *productionz; 

struct parser {
    parser_info *info;
    productionz *productions; 
    int ( *generate_productions) (lexical_store **tokens, int count);
};

const extern struct parser Parser;