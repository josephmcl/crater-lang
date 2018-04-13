/*io.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "io.h"

#define LINE_SIZE 74



static void _append_byte(file_info_t *file_info, uint8_t byte) {
    if (file_info->length == file_info->capacity) {
        file_info->capacity += LINE_SIZE;
        file_info->content = (uint8_t *) realloc(
            file_info->content, 
            file_info->capacity * sizeof(uint8_t)
        );       
    }
    file_info->content[file_info->length] = byte;
    file_info->length += 1; // TODO: we'll need to specify a max here
}

file_info_t read_file(const char *path, const char *options) {
    FILE *f;
    uint8_t b;
    file_info_t rv = {0};

    f = NULL;
    f = fopen(path, options);
    if (f == NULL)
        exit(-1); //TODO: we'll do exceptions later...

    rv.content = calloc(0, sizeof(uint8_t));
    while ((b = (uint8_t) fgetc(f)) != EOF) {
        if (feof(f)) 
            break;
        _append_byte(&rv, b);
    }    
    fclose(f); 
    return rv;
} 