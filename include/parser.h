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

const extern struct parser Parser;

#endif