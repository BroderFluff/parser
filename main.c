#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int main(void)
{
    printf("begin parsen\n");
    struct lexer lex;
    lex.c = lex.str = "hej";

    printf("str to lex: %s\n", lex.str);

    while (!is_eof(&lex))
    {
        struct token tok;
        next_token(&lex, &tok);
        printf("found token: %s\n", tok.str);
    }
}