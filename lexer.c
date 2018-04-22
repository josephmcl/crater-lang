/*lexer.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "lexer.h"

#define TOKENS_SIZE 25

/* The struct in which the lexer operates on. */
static file_info TheFile = {0}; 
static lexical_info TheInfo = {0}; 

static int validate_escape(uint8_t *head, uint8_t *end) {
    uint8_t *temp;
    int escaped;

    temp = head;
    escaped = 1;
    while(end - temp >= 0) {
        if (escaped == 0 && is_escape(*temp) != 0) 
            fprintf(stderr, "%s:%d:%ld: " error_s
                " unknown escape sequence:\n\\%c"
                "\n\n"
                , TheFile.name, TheInfo.rows
                , TheInfo.line_length + temp - head, *temp
            );
        escaped = (*temp == '\\')? 0: 1;
        temp++;
    }
    return 0;
}

int lexer_read(const char *path) {
    TheFile = read_file(path, "r");

    //stack_init(TheInfo.stack);
    return 0;
}

void lexer_free() {
    free(TheFile.content);
    free(TheFile.name);
    free(TheInfo.tokens);
    //free(TheInfo.tokens);
    TheFile = (file_info) {0};
    TheInfo = (lexical_info) {0}; 
}

lexical_store lexer_next() {
    lexical_store rv, temp;
    uint8_t *offset;


    /* END_OF_CONTENT */
    if ((&TheFile.content[TheFile.length] - TheInfo.current) <= 0) {
        rv.token = END_OF_CONTENT;
        rv.end = TheInfo.current;
        return rv;
    }

    temp.token = UNKNOWN;
    temp.end = TheInfo.current;
    /* consume any whitespace */
    while (utf8_whitespace(temp.end) == 0) {
        //printf("<<%c>>", *temp.end);
        temp.end += utf8_code_point_length(*temp.end);
    }

    rv.begin = temp.end;

    /* END_OF_CONTENT */
    if ((&TheFile.content[TheFile.length] - rv.begin) <= 0) {
        rv.token = END_OF_CONTENT;
        rv.end = TheInfo.current;
        return rv;
    }
    
    /* STRING_LITERAL */
    else if ((offset = string_literal(temp.end, TheFile.end))!=temp.end) {
        validate_escape(temp.end, offset);

        rv.end = offset;
        rv.token = STRING_LITERAL;
    }

    /* LINE_COMMENT */
    else if ((offset = line_comment(temp.end, TheFile.end)) != temp.end) {
        rv.end = offset;
        rv.token = LINE_COMMENT;
    }

    /* FLOAT_LITERAL */
    else if ((offset = float_literal(temp.end)) != temp.end) {
        rv.end = offset;
        rv.token = FLOAT_LITERAL;
    }

    /* RATIONAL_LITERAL */
    else if ((offset = rational_literal(temp.end)) != temp.end) {
        rv.end = offset;
        rv.token = RATIONAL_LITERAL;
    }

    /* INTEGER_LITERAL */
    else if ((offset = integer_literal(temp.end)) != temp.end) {
        rv.end = offset;
        rv.token = INTEGER_LITERAL;
    }

    /* IDENTIFIER */
    else if ((offset = identifier(temp.end)) != temp.end) {
        rv.end = offset;
        rv.token = IDENTIFIER;
    }

    /* LINE END */
    else if (*temp.end == '\n') {
        rv.token = LINE_END;
        rv.end = rv.begin + 1;
    }
    else {
        rv.token = UNKNOWN;
        rv.end = rv.begin + utf8_code_point_length(*rv.begin);
    }
 
    return rv;
}

static void push_token(lexical_store token) {  
    if (TheInfo.count == TheInfo.capacity) {
        TheInfo.capacity += TOKENS_SIZE;
        TheInfo.tokens = (lexical_store *) realloc(
            TheInfo.tokens, 
            TheInfo.capacity * sizeof(lexical_store)
        );       
    }
    TheInfo.tokens[TheInfo.count] = token;
    TheInfo.count += 1; // TODO: we'll need to specify a max here    
} 

#define BLURB_SIZE 60

static uint8_t *line_blurb(uint8_t *end) { //TODO not UTF-8 safe
    int i, size;
    uint8_t *begin, *rv;
    begin = TheInfo.prior_newline;
    if (TheInfo.line_length > BLURB_SIZE)
        begin += TheInfo.line_length - BLURB_SIZE;
    if (begin + BLURB_SIZE > TheFile.end)
        size = TheFile.end - begin;
    else 
        size = BLURB_SIZE;
    rv = (uint8_t *) calloc(size + 1, sizeof(uint8_t));

    memcpy(rv, begin, size);
    for (i = 0; i < size; ++i)
        rv[i] = peroxide(rv[i]);
    return rv;

}

/* static */ uint8_t *line_blurb_with_caret(uint8_t *end) { //TODO WIP
    printf("hello");
    int i, offset, size, cp_count;
    uint8_t *begin, *rv;
    offset = 0;
    cp_count = 0;
    begin = TheInfo.prior_newline;
    if (TheInfo.line_length > BLURB_SIZE)
        begin += TheInfo.line_length - BLURB_SIZE;

    while (utf8_code_point_length(*begin) == 0) {
        begin += 1;
        offset += 1;
    }
    size = BLURB_SIZE + 1 - offset;
    rv = (uint8_t *) calloc(size * 2, sizeof(uint8_t));
    memcpy(rv, begin, size);
    rv[size] = '\n';

    for (i = 0; i < size; ++i)
        rv[i] = peroxide(rv[i]);
    for (; i < size * 2 - 1; ++i)
        rv[i] = ' ';
    i = 0;
    
    while (i < size)
        cp_count += utf8_code_point_length(*(begin + i));
    rv[cp_count] = '^';
    
    return rv;

}



int analyze() {
    int token_length;
    lexical_store next;    
    uint8_t *temp;

    TheInfo.capacity = 0;
    TheInfo.count = 0;
    TheInfo.columns = 0;
    TheInfo.rows = 1;
    TheInfo.index = 0;
    TheInfo.current = TheFile.content;
    TheInfo.prior_newline = TheFile.content;
    TheInfo.line_length = 0;

    token_length = 0;
    while ((next = lexer_next()).token != END_OF_CONTENT) {
        token_length = next.end - next.begin;
        TheInfo.line_length += token_length + next.begin - TheInfo.current;

        switch (next.token) {
        case LINE_END: {
            TheInfo.rows += 1;
            if (TheInfo.line_length > TheInfo.rows)
                TheInfo.columns = TheInfo.line_length;
            TheInfo.line_length = 0;
            TheInfo.prior_newline = next.end;
            push_token(next);
        } break;
        case LINE_COMMENT:
        case STRING_LITERAL: case RATIONAL_LITERAL:
        case FLOAT_LITERAL: case INTEGER_LITERAL:
        case IDENTIFIER: {
            push_token(next);
        } break;
        default: {
            temp = line_blurb(next.end);
            fprintf(stderr, "%s:%d:%d: "error_s
                " unknown symbol" "\n"
                "%s" "\n\n"
                , TheFile.name, TheInfo.rows
                , TheInfo.line_length, temp
            );
            free(temp);
            TheInfo.state = -1;
        }
        }

        /* move the head up to the end of the current token */
        TheInfo.current += next.end - TheInfo.current;
    }
    return 0;
} 

void lexer_print() {
    int i, j, token_length;
    lexical_store *token;
    uint8_t *temp;
    
    for (i = 0; i < TheInfo.count; i++) {
        token = &TheInfo.tokens[i];
        token_length = token->end - token->begin;
        printf("%s ", token_names[token->token]);
        temp = (uint8_t *) calloc(token_length + 1, sizeof(uint8_t));

        memcpy(temp, token->begin, token_length);

        for (j = 0; j < token_length; ++j)
            temp[j] = bleach(temp[j]);

        // printf("[%d] [%s]\n", token_length, temp);

        free(temp);
    }
    printf("\n");
    return;
}

const struct lexer Lexer = {
    .file = &TheFile,
    .info = &TheInfo,
    .read = lexer_read,
    .free = lexer_free,
    .analyze = analyze,
    .print = lexer_print
};
