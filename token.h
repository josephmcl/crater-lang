/*token.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include <stdint.h>
#include <stdio.h>

enum Token {
    
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


int utf8_code_point_cmp(uint8_t *a, uint8_t *b);

int utf8_whitespace(uint8_t *code_point);

int utf8_code_point_length(uint8_t c);

int utf8_code_point_to_int(uint8_t *code_point);