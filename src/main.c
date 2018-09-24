#include <stdlib.h>
#include <stdio.h>
#include "vm.h"
#include "cmd_parse.h"

int main(void)
{
    struct vm_context *vm = vm_alloc(256);
    vm_init(vm, "setLEDCount 20\n   setLEDCount ll");

    vm_execute(vm);

    vm_free(vm);

    /*
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
    
    lexer_free(lex);*/
}
