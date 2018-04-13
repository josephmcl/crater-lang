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

typedef struct file_info_s file_info_t;

struct file_info_s {
    uint8_t *content;
    int length; 
    int capacity;
};

file_info_t read_file(const char *path, const char *options);

#endif