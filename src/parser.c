/*parser.c
  Copyright ©2018 Joseph McLaughlin
  This file is covered by the MIT license. Refer to the LICENSE file in 
  the root directory of this project for more information.  
 */
#include "parser.h"
#include "stack.h"

static parser_info TheInfo = {0};

// top 
//      : invariant_defs
// invariant_defs
//      : e
//      | invariant_defs invariant_def
// invariant_def 
//      : IDENTIFIER COLON tokens LINE_END productions SEMICOLON
// productions 
//      : empty
//      | productions production
// production
//      : LINE tokens LINE_END
// tokens
//      : empty
//      | tokens (*) # (*) = tokens besides LINE_END


// TODO: write
//static int pg_evaluate(stack_t *s, void *item);
// TODO: write
//static int pg_reduce(stack_t *s, void *item);


int parser_generate(void) {
    lexical_token token;
    size_t i;
    stack_t s;
    lexical_store *store;
    int result, excess;
    
    s = stack_init();

    i = 0; excess = 1;
    while ((token = Lexer.token(i)) != UNKNOWN && token != END_OF_CONTENT) {

        store = Lexer.store(i);

        switch (store->token) {
        case LINE_END: {
            if (excess == 0) {
                result = pg_evaluate(&s, (void *) store);
                if (result == 0)
                    stack_push(&s, (void *) store);
                else if (result > 0) 
                    pg_reduce(s, (void *) result);
                else 
                    ; // conflicts 
                stack_push(&s, (void *) store);
                excess = 1;
            }
        } break;
        case LINE_COMMENT: {
            ;
        } break;
        default: {
            excess = 0;
            result = pg_evaluate(&s);
            if (result == 0) 
                stack_push(&s, (void *) store);
            else if (result > 0) 
                pg_reduce(s, result);
            else 
                ; // conflicts 
            
        } break;
        }

        
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

