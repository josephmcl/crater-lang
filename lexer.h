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

enum lexical_token {
    
    identifier,
    integer_literal_decimal,
    /*
    integer_literal_binary,
    integer_literal_octal,
    integer_literal_hexidecimal,
    float_literal,
    string_literal,
    */
    nil,
    true_,
    false_,


    parentheses_left,
    parentheses_right,
    /*
    bracket_square_left,
    bracket_square_right,
    bracket_curly_left,
    bracket_curly_right,
    */

    assignment_owned,
    //assignment_unowned,

    operator_plus,
    operator_minus,
    operator_multiplication,
    operator_division,
    operator_integer_division,
    operator_exponent,

    /*
    logical_not,
    logical_and,
    logical_or,
    logical_xor
    */

    equals,
    atmost,
    less,
    atleast,
    greater,

    /*
    bitwise_not,
    bitwise_and,
    bitwise_or,
    bitwise_xor,

    bitshift_left,
    bitshift_right,
    */
    line_end,
    escaped_line_end

};

struct lexer {
    file_info_t *file;
    //lexical_token (*next)(void);
    int (*read)(const char *path, const char *options);
    void (*free)();
    int (*lexer)();
};

extern const struct lexer Lexer;

#endif /* CRATER_LANG_LEXER_H_ */
