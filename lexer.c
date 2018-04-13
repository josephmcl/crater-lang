/*lexer.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */

#include "lexer.h"

file_info_t TheFile = {0}; 

int lexer_read(const char *path, const char *options) {
    TheFile = read_file(path, options);
}

void lexer_free() {
    free(Lexer.file->content);
}

int utf8_lexer() {
    int i, length, j;
    uint8_t c[5];
    int lines;

    c[4] = '\0';
    i = 0; lines = 1;
    while (i < Lexer.file->length) {

        c[0] = '\0';
        c[1] = '\0';
        c[2] = '\0';
        c[3] = '\0';

        length = utf8_code_point_length(Lexer.file->content[i]);

        for (j = 0; j < length; ++j)
            c[j] = Lexer.file->content[i + j];

        
        if (Lexer.file->content[i] == '\n') lines += 1;

        if (utf8_whitespace(&Lexer.file->content[i]))
            printf("%d, \'%s\'\n", length, c);
        else
            printf(">WS: %d, \'%s\'\n", length, c);

        i += length;
    }
    printf("lines: %d\n",lines);

}


const struct lexer Lexer = {
    .file = &TheFile,
    //.next = next
    .read = lexer_read,
    .free = lexer_free,
    .lexer = utf8_lexer
};