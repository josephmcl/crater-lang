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

typedef enum {
    
    UNKNOWN = -2,
    START_OF_CONTENT = -1,
    END_OF_CONTENT = 0,
    ESACPE = 1,
    LINE_END = 2,
    LINE_COMMENT = 3,

    IDENTIFIER = 16
} lexical_token;

typedef enum {
    PURE_STATE,
    LINE_COMMENT_STATE,
    STRING_LITERAL_STATE,
    THREE_STR_LITERAL_STATE
} lexical_state;

typedef struct {
    lexical_token token;
    uint8_t *end;
} lexical_store;

typedef struct {
    lexical_store *tokens;
    lexical_state state;
    uint8_t code_point[5];
    unsigned int rows;
    unsigned int columns;
    int index;
    uint8_t *current;

} lexical_info;

struct lexer {
    file_info *file;
    lexical_info *info;
    //lexical_token (*next)(void);
    int (*read)(const char *path, const char *file);
    void (*free)();
    //int (*lexer)();
    int (*analyze)();
};

extern const struct lexer Lexer;

#endif /* CRATER_LANG_LEXER_H_ */
