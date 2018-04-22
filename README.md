# crater-lang

usage:
```c
#include "lexer.h"

int main(int argc, char **argv) {

    if (argc < 2)
        exit(-1);

    Lexer.read(argv[1]);
    
    Lexer.analyze();

    Lexer.print();

    Lexer.free();
}
```
