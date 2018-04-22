/*token.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_TOKEN_H_
#define CRATER_LANG_TOKEN_H_

#include "io.h"
#include "codepoint.h"

typedef enum {
    UNKNOWN = -2,
    START_OF_CONTENT = -1,
    END_OF_CONTENT = 0,
    ESACPE = 1,
    LINE_END = 2,
    LINE_COMMENT = 3,
    TRIPLE_STRING = 4,
    STRING_LITERAL = 5,
    RATIONAL_LITERAL = 6,
    FLOAT_LITERAL = 7,
    INTEGER_LITERAL = 8,
    IDENTIFIER = 9
} lexical_token;

typedef struct {
    lexical_token token;
    uint8_t *begin;
    uint8_t *end;
} lexical_store;

extern const char *token_names[];

uint8_t *consume_whitespace(uint8_t *head);

uint8_t *identifier(uint8_t *head);

uint8_t *integer_literal(uint8_t *head);

uint8_t *float_literal(uint8_t *head);

uint8_t *rational_literal(uint8_t *head);

uint8_t *line_comment(uint8_t *head, uint8_t *end);

uint8_t *string_literal(uint8_t *head, uint8_t *end);

int is_escape(uint8_t c);

#endif /* CRATER_LANG_TOKEN_H_ */