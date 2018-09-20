#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int main(void)
{
    printf("begin parsen\n");
    struct lexer lex;
    lexer_init_str(&lex, "hej kaka apa 1 2 9");

    printf("str to lex: %s\n", lex.str);

    while (!lexer_is_eof(&lex))
    {
        struct token tok;
        lexer_next_token(&lex, &tok);
        printf("found token: %s\n", tok.str);
    }
}
