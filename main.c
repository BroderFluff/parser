#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int main(void)
{
    printf("begin parsen\n");
    struct lexer lex;
    lex.c = lex.str = "hej kaka apa 1 2 9";

    printf("str to lex: %s\n", lex.str);

    while (!is_eof(&lex))
    {
        struct token tok;
        tok.len = 0;
        next_token(&lex, &tok);
        printf("found token: %s\n", tok.str);
    }
}
