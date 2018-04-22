/*token.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "token.h"

const char *token_names[] = {
    "END_OF_CONTENT",
    "ESACPE",
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
        while (is_alphanum(*head) == 0)
            head += 1; 
    return head;
}

uint8_t *integer_literal(uint8_t *head) {
    if (is_digit(*head) == 0)      
        while (is_digit(*head) == 0)
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
    if (*rv == '#')      
        while (*rv != '\n') {
            if (end - rv <= 0)
                return head;
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