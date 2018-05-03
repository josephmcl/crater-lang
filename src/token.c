/*token.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "token.h"

const char *token_names[] = {
    "END_OF_CONTENT",
    "ESCAPE",
    "LINE_END",
    "LINE_COMMENT",
    "TRIPLE_STRING",
    "STRING_LITERAL",
    "RATIONAL_LITERAL",
    "FLOAT_LITERAL",
    "INTEGER_LITERAL",
    "IDENTIFIER"
};

/*static*/ int ustrncmp(const uint8_t *s1, const uint8_t *s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
        --n;
    }
    if (n == 0)
        return 0;
    else
        return (*(uint8_t *)s1 - *(uint8_t *)s2);
}

int is_escape(uint8_t c) {
    switch (c) {
    default: 
        return 1;
    case 'a':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
    case 'v':
    case '\\':
    case '\'':
    case '\"':
        return 0;
    }
} 

uint8_t *identifier(uint8_t *head) {
    if (is_alpha(*head) == 0)  
        while (is_alphanum(*head) == 0 || *head == '_')
            head += 1; 
    return head;
}

uint8_t *integer_literal(uint8_t *head) {
    if (is_digit19(*head) == 0)      
        while (is_digit(*head) == 0)
            head += 1;
    else if (*head == '0')
        head += 1;
    return head;
}

uint8_t *float_literal(uint8_t *head) {
    uint8_t *rv;
    rv = head;
    if (is_digit(*rv) == 0)      
        while (is_digit(*rv) == 0) {
            rv += 1;
        }
    else
        return head;
    if (*rv != '.')
        return head;
    rv++;
    if (is_digit(*rv) == 0)      
        while (is_digit(*rv) == 0) {
            rv += 1;
        }
    else 
        return head;

    return rv;
}

uint8_t *rational_literal(uint8_t *head) {
    uint8_t *rv;
    rv = head;
    if (is_digit(*rv) == 0)      
        while (is_digit(*rv) == 0) {
            rv += 1;
        }
    else
        return head;
    rv = consume_whitespace(rv);
    if (*rv != '/')
        return head;
    rv++;
    rv = consume_whitespace(rv);
    if (is_digit(*rv) == 0)      
        while (is_digit(*rv) == 0) {
            rv += 1;
        }
    else 
        return head;

    return rv;
}

uint8_t *consume_whitespace(uint8_t *head) {
    while (utf8_whitespace(head) == 0) {
        head += utf8_code_point_length(*head);
    }
    return head; 
}

uint8_t *line_comment(uint8_t *head, uint8_t *end) {
    uint8_t *rv;

    rv = head;
    if (*rv == '#') {     
        while (end - rv > 0 && *rv != '\n') 
            rv += utf8_code_point_length(*rv);
    }
    return rv;
}

uint8_t *string_literal(uint8_t *head, uint8_t *end) {
    uint8_t state;
    uint8_t *rv;
    int escaped;

    escaped = 1;
    rv = head;
    if (*rv != '\"' && *rv != '\'')
        return head;
    state = *rv;
    rv += 1;
    while (*rv != state || escaped == 0) {
        if (end - rv <= 0 || *rv == '\n')
            return head;
        escaped = (*rv == '\\')? 0: 1;
        rv += utf8_code_point_length(*rv);
    }
    rv += 1;
    return rv;
}

/*
uint8_t *triple_string(uint8_t *head, uint8_t *end) {
    uint8_t *rv;

    rv = head;
    if (rv != "\"\"\"")
        return head;
    rv += 3;
    while (rv != "\"\"\"") {
        if (end - rv <= 0)
            return head;
        rv += utf8_code_point_length(*rv);
    }
    rv += 3;
    return rv;
}
*/
static uint8_t multi_byte_tokens[8 * 3] = {
    "->\t"
    "::\t"
    "<<\t"
    ">>\t"
    "<=\t"
    ">=\t"
    "!=\t"
    "**\t"
};

#define MB_TOKS 8
#define MB_TOKS_OFFSET 3

uint16_t multi_byte_token(uint8_t *s, uint8_t *end) {
    int i, j;
    uint8_t *temp, *stamp;

    stamp = multi_byte_tokens;
    for (i = 0; i < MB_TOKS; ++i) {
        j = 0;
        temp = s;
        while (end - temp > 0 && *(temp + j) == *(stamp + j))
            j += 1;

        if (*(stamp + j) == '\t') {
            return 
                ((i + MULTI_BYTE_TOKENS) << 0x8) + j;
        }
        stamp += MB_TOKS_OFFSET;
    }
    return 0;
}

static uint8_t keyword_tokens[22 * 8] = { //45
    "class\t  "
    "def\t    "
    "init\t   "
    "return\t "
    "extends\t"
    "derives\t"
    "expects\t"
    "causes\t " 
    "true\t   "
    "false\t  "
    "nil\t    "
    "and\t    "
    "or\t     "
    "not\t    "
    "if\t     "
    "elif\t   "
    "else\t   "
    "while\t  "
    "for\t    "
    "var\t    "
    "let\t    "
    "set\t    "
};

#define KY_TOKS 22
#define KY_TOKS_OFFSET 8

uint16_t keyword_token(uint8_t *s, uint8_t *end) {
    int i, j;
    uint8_t *temp, *stamp;

    stamp = keyword_tokens;
    for (i = 0; i < KY_TOKS; ++i) {
        j = 0;
        temp = s;
        while (end - temp > 0 && *(temp + j) == *(stamp + j))
            j += 1;

        if (*(stamp + j) == '\t') {
            return 
                ((i + KEYWORD_TOKENS) << 0x8) + j;
        }
        stamp += KY_TOKS_OFFSET;
    }
    return 0;
}



lexical_token single_byte_token(uint8_t c) {
    switch (c) {
    case '+': return PLUS;
    case '-': return MINUS;
    case '*': return STAR;
    case '/': return SLASH;
    case '^': return CARET;
    case '~': return TILDA;
    case ':': return IS;
    case ';': return MANUAL_LINE_END;
    case ',': return COMMA;
    case '.': return DOT;
    case '(': return LPARENTHESES;
    case ')': return RPARENTHESES;
    case '[': return LSQUARE;
    case ']': return RSQUARE;
    case '{': return LCURLY;
    case '}': return RCURLY;
    case '<': return LANGLE;
    case '>': return RANGLE;
    case '?': return QUESTION;
    case '&': return AMPERSAND;
    case '|': return LINE;
    case '!': return EXCLAIM;
    case '%': return PERCENT;
    case '=': return EQUALS;

    default: return UNKNOWN;
    }
}