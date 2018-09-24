#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "token.h"
#include "cmd_parse.h"

int main(void)
{
    struct lexer *lex = lexer_alloc();
    lexer_init_str(lex, "setLEDCount 20\nsetLEDCount ll");

    while (!lexer_is_eof(lex)) {
        parse_next_command(lex);
        if (cmd) {
            printf("num params: %d\n", cmd->num_params);
            printf("param 0: %d\n", cmd->params[0]);
        } else {
            printf("command parse failed..\n");
        }
    }
    
    lexer_free(lex);
}
