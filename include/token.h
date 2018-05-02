/*token.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_TOKEN_H_
#define CRATER_LANG_TOKEN_H_

#include "io.h"
#include "codepoint.h"

#define TOKEN_SECTION 32
#define TOKEN_PACK 
#define MULTI_BYTE_TOKENS 32
#define SINGLE_BYTE_TOKENS 64
#define KEYWORD_TOKENS 96

typedef enum {
    UNKNOWN          = -2,
    START_OF_CONTENT = -1, // TODO: unused
    END_OF_CONTENT   = 0, 
    ESCAPE           = 1,
    LINE_END         = 2,
    LINE_COMMENT     = 3,
    TRIPLE_STRING    = 4,
    STRING_LITERAL   = 5,
    RATIONAL_LITERAL = 6,
    FLOAT_LITERAL    = 7,
    INTEGER_LITERAL  = 8,
    IDENTIFIER       = 9,
    
    ARROW            = MULTI_BYTE_TOKENS,     // ->
    DEFINE           = MULTI_BYTE_TOKENS + 1, // ::
    DOUBLE_LANGLE    = MULTI_BYTE_TOKENS + 2, // <<
    DOUBLE_RANGLE    = MULTI_BYTE_TOKENS + 3, // >>
    LANGLE_EQUALS    = MULTI_BYTE_TOKENS + 4, // <=
    RANGLE_EQUALS    = MULTI_BYTE_TOKENS + 5, // >=
    EXCLAIM_EQUALS   = MULTI_BYTE_TOKENS + 6, // !=
    STAR_STAR        = MULTI_BYTE_TOKENS + 7, // **

    /* the whole freaking english keyboard range */
    PLUS             = SINGLE_BYTE_TOKENS,      // +
    MINUS            = SINGLE_BYTE_TOKENS + 1,  // -
    STAR             = SINGLE_BYTE_TOKENS + 2,  // *
    SLASH            = SINGLE_BYTE_TOKENS + 3,  // /
    CARET            = SINGLE_BYTE_TOKENS + 4,  // ^
    TILDA            = SINGLE_BYTE_TOKENS + 5,  // ~
    IS               = SINGLE_BYTE_TOKENS + 6,  // :
    MANUAL_LINE_END  = SINGLE_BYTE_TOKENS + 7,  // ;
    COMMA            = SINGLE_BYTE_TOKENS + 8,  // ,
    DOT              = SINGLE_BYTE_TOKENS + 9,  // .
    LPARENTHESES     = SINGLE_BYTE_TOKENS + 10, // (
    RPARENTHESES     = SINGLE_BYTE_TOKENS + 11, // )
    LSQUARE          = SINGLE_BYTE_TOKENS + 12, // [
    RSQUARE          = SINGLE_BYTE_TOKENS + 13, // ]
    LCURLY           = SINGLE_BYTE_TOKENS + 14, // {
    RCURLY           = SINGLE_BYTE_TOKENS + 15, // }
    LANGLE           = SINGLE_BYTE_TOKENS + 16, // <
    RANGLE           = SINGLE_BYTE_TOKENS + 17, // >
    QUESTION         = SINGLE_BYTE_TOKENS + 18, // ?
    AMPERSAND        = SINGLE_BYTE_TOKENS + 19, // &
    LINE             = SINGLE_BYTE_TOKENS + 20, // |
    EXCLAIM          = SINGLE_BYTE_TOKENS + 21, // !
    PERCENT          = SINGLE_BYTE_TOKENS + 22, // %
    EQUALS           = SINGLE_BYTE_TOKENS + 23, // =

    CLASS            = KEYWORD_TOKENS,      // class
    DEF              = KEYWORD_TOKENS + 1,  // def
    INIT             = KEYWORD_TOKENS + 2,  // init
    RETURN           = KEYWORD_TOKENS + 3,  // return
    EXTENDS          = KEYWORD_TOKENS + 4,  // extends
    DERIVES          = KEYWORD_TOKENS + 5,  // derives
    EXPECTS          = KEYWORD_TOKENS + 6,  // expects
    CAUSES           = KEYWORD_TOKENS + 7,  // causes 
    TRUE_LIT         = KEYWORD_TOKENS + 8,  // true
    FALSE_LIT        = KEYWORD_TOKENS + 9,  // false
    NIL              = KEYWORD_TOKENS + 10, // nil
    AND              = KEYWORD_TOKENS + 11, // and 
    OR               = KEYWORD_TOKENS + 12, // or
    NOT              = KEYWORD_TOKENS + 13, // not
    IF               = KEYWORD_TOKENS + 14, // if
    ELIF             = KEYWORD_TOKENS + 15, // elif
    ELSE             = KEYWORD_TOKENS + 16, // else
    WHILE            = KEYWORD_TOKENS + 17, // while
    FOR              = KEYWORD_TOKENS + 18, // for
    VAR              = KEYWORD_TOKENS + 19, // var
    LET              = KEYWORD_TOKENS + 20, // let 
    SET              = KEYWORD_TOKENS + 21, // set

} lexical_token;

typedef struct {
    lexical_token token;
    uint8_t *begin;
    uint8_t *end;
} lexical_store;

extern const char *token_names[];


/* returns matched token */
lexical_token single_byte_token(uint8_t c);

/* returns matched token in the upper byte 
   and matched sequence length in the lower byte
   otherwise returns 0
 */
uint16_t multi_byte_token(uint8_t *head, uint8_t *end);
uint16_t keyword_token(uint8_t *head, uint8_t *end);

/* returns head + matched sequence length */
uint8_t *consume_whitespace(uint8_t *head);
uint8_t *identifier(uint8_t *head);
uint8_t *integer_literal(uint8_t *head);
uint8_t *float_literal(uint8_t *head);
uint8_t *rational_literal(uint8_t *head);
uint8_t *line_comment(uint8_t *head, uint8_t *end);
uint8_t *string_literal(uint8_t *head, uint8_t *end);

int is_escape(uint8_t c);



#endif /* CRATER_LANG_TOKEN_H_ */