#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "token.h"

int main(void)
{
    printf("begin parsen\n");
    struct lexer *lex = lexer_alloc();
    lexer_init_str(lex, "hej kaka apa 1 2 9 kakor er mums");

    struct token *tok = token_alloc();

    while (!lexer_is_eof(lex)) {
        lexer_next_token(lex, tok);
        switch (token_get_type(tok)) {
            case TT_NAME:
                printf("Found TT_NAME : %s\n", token_get_name(tok));
                break;
            case TT_INTEGER:
                printf("Found TT_INTEGER : %d\n", token_get_integer(tok));
                break;
            case TT_NONE:
            default:
            break;
        }
    }

    lexer_free(lex);
    token_free(tok);
}
