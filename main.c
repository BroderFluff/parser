#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "token.h"
#include "cmd_parse.h"

int main(void)
{
    struct lexer *lex = lexer_alloc();
    lexer_init_str(lex, "setLEDCount 20 setLEDCount 30");

    while (!lexer_is_eof(lex)) {
        struct command *cmd = parse_next_command(lex);
        if (cmd) {
            printf("num params: %d\n", cmd->num_params);
            printf("param 0: %d\n", cmd->params[0]);
        } else {
            printf("command parse failed..\n");
        }
    }
    


#if 0
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
#endif

    lexer_free(lex);
}
