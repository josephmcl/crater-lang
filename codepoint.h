/*codepoint.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_CODEPOINT_H_
#define CRATER_LANG_CODEPOINT_H_

#include <stdint.h>
#include <stdio.h>

int utf8_code_point_cmp(uint8_t *a, uint8_t *b);

int utf8_whitespace(uint8_t *code_point);

int utf8_code_point_length(uint8_t c);

int utf8_code_point_to_int(uint8_t *code_point);

#endif