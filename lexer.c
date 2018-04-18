/*lexer.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */

#include "lexer.h"

//static const file_info EmptyFileInfo = {0};
//static const lexical_info EmptyLexicalInfo = {0};

/* The struct in which the lexer operates on. */
static file_info TheFile = {0}; 
static lexical_info TheInfo = {0}; 



int lexer_read(const char *path) {
    TheFile = read_file(path, "r");
    //stack_init(TheInfo.stack);
    return 0;
}

void lexer_free() {
    free(TheFile.content);
    free(TheFile.name);
    //free(TheInfo.tokens);
    TheFile = (file_info) {0};
    TheInfo = (lexical_info) {0}; 
}

lexical_store lexer_next() {
    lexical_store rv, temp;
    int code_point_length;

    rv.token = UNKNOWN;
    rv.end = TheInfo.current;


    /* consume any whitespace */
    while (utf8_whitespace(rv.end) == 0) {
        rv.end += utf8_code_point_length(*rv.end);
    }

    //TODO: I'd like to not modify this struct in this function,
    //find another way of communicating how much whitespace there was
    TheInfo.current = rv.end;  

    if ((&TheFile.content[TheFile.length] - TheInfo.current) <= 0) {
        rv.token = END_OF_CONTENT;
        return rv;
    }

    temp.token = rv.token;
    temp.end = rv.end;
    
    code_point_length = utf8_code_point_length(*rv.end);

    /* FLOAT LITERAL
    if (utf8_code_point_numeric(*rv.end) == 0) {
        rv.token = INTEGER_DECIMAL_LITERAL;
        while (utf8_code_point_numeric(*(rv.end + code_point_length)) == 0){
            rv.end += code_point_length;
            code_point_length = utf8_code_point_length(*rv.end);
        }
        if(*rv.end == '.') {
            rv.end += code_point_length;
            code_point_length = utf8_code_point_length(*rv.end);
            while (utf8_code_point_numeric(*(rv.end + code_point_length)) == 0){
                rv.end += code_point_length;
                code_point_length = utf8_code_point_length(*rv.end);
            }
        }

        else if (*temp.end == '0') {
            else if (*temp.end == 'x') {

            }
        }
    }
    */

    /* INTEGER DECIMAL LITERAL */
    if (utf8_code_point_numeric(*rv.end) == 0) {
        temp.token = INTEGER_DECIMAL_LITERAL;
        while (utf8_code_point_numeric(*(rv.end + code_point_length)) == 0){
            rv.end += code_point_length;
            code_point_length = utf8_code_point_length(*rv.end);
        }
    }

    /* IDENTIFIER */
    if (utf8_code_point_alpha(*rv.end) == 0) {
        rv.token = IDENTIFIER;
        while (cp_alphanum(*(rv.end + code_point_length)) == 0){
            rv.end += code_point_length;
            code_point_length = utf8_code_point_length(*rv.end);
        }
    }

    /* LINE END */
    else if (*rv.end == '\n') {
        rv.token = LINE_END;
    }
 
    return rv;
}

int analyze() {
    int token_length;
    static int line_length;
    lexical_store next;
    uint8_t *temp;
    
    TheInfo.rows = 1;
    TheInfo.index = 0;
    TheInfo.current = TheFile.content;
    TheInfo.prior_newline = TheFile.content;

    line_length = 0;
    while ((next = lexer_next()).token != END_OF_CONTENT) {
        token_length = next.end + 1 - TheInfo.current;
        line_length += token_length;

        switch (next.token) {
        case LINE_END: {
            TheInfo.rows += 1;
            if (line_length > TheInfo.rows)
                TheInfo.columns = line_length;
            line_length = 0;
            printf("new line (%d so far)\n", TheInfo.rows);
        } break;
        case INTEGER_DECIMAL_LITERAL: {
            temp = (uint8_t *) calloc(0, token_length * sizeof(uint8_t));

            memcpy(temp, TheInfo.current, token_length);

            printf("<%s>[%d]\n", temp, token_length);

            free(temp);
        } break;
        case IDENTIFIER: {
            temp = (uint8_t *) calloc(0, token_length * sizeof(uint8_t));

            memcpy(temp, TheInfo.current, token_length);

            printf("<%s>[%d]\n", temp, token_length);

            free(temp);
        } break;
        default: {
            fprintf(stderr, "%s:%d:%d: \033[31;1merror:\033[0m "
                "unknown symbol"
                "\n"
                , TheFile.name, TheInfo.rows, line_length
            );
            TheInfo.state = -1;
        }
        }

        

        TheInfo.current += token_length;
    }
    printf("END OF CONTENT. Lexical analysis complete.\n");
    return 0;
} 

const struct lexer Lexer = {
    .file = &TheFile,
    .info = &TheInfo,
    .read = lexer_read,
    .free = lexer_free,
    .analyze = analyze
};