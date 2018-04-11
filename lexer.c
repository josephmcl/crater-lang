#include "lexer.h"

#define LINE_SIZE 74

struct file_info_s {
    uint8_t *content;
    int byte_length;
    int capacity;
};

static void _append_byte(file_info_t *file_info, uint8_t byte) {
    if (file_info->byte_length == file_info->capacity) {
        file_info->capacity += LINE_SIZE;
        file_info->content = (uint8_t *) realloc(
            file_info->content, 
            file_info->capacity * sizeof(uint8_t)
        );       
    }
    file_info->content[file_info->byte_length] = byte;
    file_info->byte_length += 1; // TODO: we'll need to specify a max here
}

file_info_t *read_file(const char *path, const char *options) {
    FILE *f;
    uint8_t b;
    file_info_t *rv;

    f = NULL;
    f = fopen(path, options);
    if (f == NULL)
        exit(-1); //TODO: we'll do exceptions later...

    rv = (file_info_t *) calloc(0, sizeof(file_info_t));
    rv->content = calloc(0, sizeof(uint8_t));
    while ((b = (uint8_t) fgetc(f)) != EOF) {
        if (feof(f)) 
            break;
        _append_byte(rv, b);
    }    
    fclose(f); 
    return rv;
} 

int utf8_lexer(file_info_t *s) {
    int i, length, j;
    uint8_t c[5];
    int lines;

    c[4] = '\0';
    i = 0; lines = 1;
    while (i < s->byte_length) {

        c[0] = '\0';
        c[1] = '\0';
        c[2] = '\0';
        c[3] = '\0';

        length = utf8_code_point_length(s->content[i]);

        for (j = 0; j < length; ++j)
            c[j] = s->content[i + j];

        
        if (s->content[i] == '\n') lines += 1;

        printf("%d, \'%s\'\n", length, c);

        i += length;
    }
    printf("lines: %d\n",lines);

}


int whitespace(unsigned char c) {
    switch (c) {
    case ' ':
        return 1;
    case '\t':
        return 1;
    case '\r':
        return 1;
    case '\f':
        return 1;
    default:
        return 0;    
    }
}





int utf8_code_point_length(uint8_t c) {
    if ((c & 0x80) == 0) 
        return 1;
    if ((c & 0x20) == 0)
        return 2;
    if ((c & 0x10) == 0)
        return 3;
    if ((c & 0x8) == 0)
        return 4;
    return 0; //TODO: this won't do
}