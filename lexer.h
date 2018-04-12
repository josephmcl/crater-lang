/*lexer.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CRATER_LANG_LEXER_H_
#define CRATER_LANG_LEXER_H_

typedef struct file_info_s file_info_t;

file_info_t *read_file(const char *path, const char *options);

int utf8_lexer(file_info_t *s);

#endif /* CRATER_LANG_LEXER_H_ */
