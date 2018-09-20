#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"

int main(void)
{
    printf("begin parsen\n");
    struct lexer lex;
    lexer_init_str(&lex, "hej kaka apa 1 2 9");

    printf("str to lex: %s\n", lex.str);

    while (!lexer_is_eof(&lex)) {
        struct token tok;
        lexer_next_token(&lex, &tok);

        switch (tok.type) {
            case TT_NAME:
                printf("Found TT_NAME : %s", token_as_name(&tok));
                break;
            case TT_INTEGER:
                printf("Found TT_INTEGER : %d", token_as_integer(&tok));
                break;
            case TT_NONE:
            default:
            break;
        }
    }
}
