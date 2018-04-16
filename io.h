/*io.h
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#ifndef CRATER_LANG_IO_H_
#define CRATER_LANG_IO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define log()

#define notice_c(f_, ...) fprintf(stderr,\
    ("(" ANSI_COLOR_GREEN "notice"\
    ANSI_COLOR_RESET ") " f_), __VA_ARGS__);

#define warning_c(f_, ...) fprintf(stderr,\
    ("(" ANSI_COLOR_YELLOW "warning"\
    ANSI_COLOR_RESET ") " f_), __VA_ARGS__);

#define error_c(f_, ...) fprintf(stderr,\
    ("(" ANSI_COLOR_RED "error"\
    ANSI_COLOR_RESET ") " f_), __VA_ARGS__);

typedef struct file_info_s file_info;

struct file_info_s {
    uint8_t *content;
    int length; 
    int capacity;
};

file_info read_file(const char *path, const char *options);

#endif