/*parser.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "parser.h"
#include "stack.h"

static parser_info TheInfo = {0};
static production *TheProductions;

static void _append_production(production p) {
    production *temp;
    if (TheInfo.length == TheInfo.capacity) {
        TheInfo.capacity += 10;

        temp = realloc(
            TheProductions, 
            TheInfo.capacity * sizeof(uint8_t)
        );  
        if (temp == NULL)
            exit(-1);
        TheProductions = temp;
    }
    TheProductions[TheInfo.length] = p;
    TheInfo.length += 1; // TODO: we'll need to specify a max here
}

int parser_generate(void) {
    lexical_token token;
    size_t i;
    stack_t s;
    lexical_store *store;
    s = stack_init();



    i = 0;
    while ((token = Lexer.token(i)) != UNKNOWN && token != END_OF_CONTENT) {

        store = Lexer.store(i);
        stack_push(&s, (void *) store);
        printf("%d ", store->token);
        i += 1;
    }
    
    printf("\n");

    i = 0;
    do {
        if (stack_peek(&s) == NULL)
            printf("<?> ");    
        else {
            store = (lexical_store *) stack_peek(&s);
            printf("%d ", store->token);
        }
        i += 1;
    } while (stack_pop(&s) == 0);

    printf("\n");
    
    stack_free(&s);

    return 0;
}




const struct parser Parser = {
    .info = &TheInfo,
    .generate = parser_generate

};
