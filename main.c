#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int main(void)
{
    printf("begin parse");
    struct lexer lex;
    lex.c = lex.str = "hej 1 2 3";

    printf("str to lex: %s", lex.str);

    while (!is_eof(&lex))
    {
        struct token tok;
        next_token(&lex, &tok);
        printf("found token: %s", tok.str);
    }
}