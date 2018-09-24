#include "vm.h"
#include "lexer.h"
#include "cmd_parse.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct vm_context {
    int     status;
    int     capacity;
    int     length;
    int     inst_base[];
};

struct vm_context *vm_alloc(int capacity)
{
    struct vm_context *vm = malloc(sizeof (struct vm_context) + sizeof(int) * capacity);
    assert(vm /* Out of memory! */);

    vm->capacity = capacity;
    vm->length = 0;
    vm->status = 0;

    return vm;
}

void vm_init(struct vm_context *vm, const char *str)
{
    if (!str || strlen(str) <= 0) {
        printf("No string data to parse!");
        return;
    }

    int index = 0;
    struct lexer *lex = lexer_alloc();
    lexer_init_str(lex, str);
    while (!lexer_is_eof(lex)) {
        index += parse_next_inst(lex, &vm->inst_base[index]);
    }

    if (lex) {
        lexer_free(lex);
    }
}

void vm_free(struct vm_context *vm)
{
    if (!vm) {
        return;
    }
    free(vm);
}

int vm_execute(const struct vm_context *vm)
{
    int current_inst = vm->inst_base[0];
    while (current_inst) {

    }

    return 0;
}

