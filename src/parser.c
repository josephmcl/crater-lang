/*parser.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "parser.h"

static parser_info TheInfo = {0};
static production *productions;


int parser_generate_productions(lexical_store **tokens, int count) {

    return 0;
}




const struct parser Parser = {
    .info = &TheInfo,
    .productions = &productions,
    .generate_productions = parser_generate_productions

};
