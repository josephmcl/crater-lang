#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CRATER_LANG_LEXER_H_
#define CRATER_LANG_LEXER_H_

typedef struct file_info_s file_info_t;

file_info_t *read_file(const char *path, const char *options);

int utf8_code_point_length(uint8_t c);

int utf8_lexer(file_info_t *s);

#endif /* CRATER_LANG_LEXER_H_ */
