/*lexer.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_LEXER_H_
#define CRATER_LANG_LEXER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "codepoint.h"
#include "token.h"

typedef struct {
    int count;
    int capacity;
    lexical_store *tokens;
    unsigned int rows;
    unsigned int columns;
    unsigned int line_length;
    int index; // TODO remove ? 
    uint8_t *current; 
    int state;
    uint8_t *prior_newline;
} lexical_info;

struct lexer {
    file_info *file;
    lexical_info *info;
    int (*read)(const char *path);
    void (*free)();
    int (*analyze)();
    void (*print)();
};

extern const struct lexer Lexer;

#endif /* CRATER_LANG_LEXER_H_ */
