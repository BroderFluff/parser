#include "vm.h"
#include "lexer.h"
#include "cmd_parse.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef int inst_t;

struct vm_context {
    int         status;
    size_t      capacity;
    size_t      length;
    int         inst_base[];
};

struct vm_context *vm_alloc(const size_t capacity)
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

    size_t index = 0;
    struct lexer *lex = lexer_alloc();
    lexer_init_str(lex, str);
    while (!lexer_is_eof(lex)) {
        index += parse_next_command(lex, &vm->inst_base[index]);
        if (index >= vm->capacity) {
            printf("Ran out of instruction-memory while parsing!!!");
            return;
        }
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

static void set_debug()
{

}

static int get_version_number()
{
    return 0;
}

static void set_led_count(int a)
{
    printf("set_led_count(%d)\n", a);
}

int vm_execute(const struct vm_context *vm)
{
    const int *inst = &vm->inst_base[0];
    while (*inst) {
        switch (*inst) {
            case CMD_SET_DEBUG:
                break;
            case CMD_GET_VERSION_NUMBER:
                break;
            case CMD_SET_LED_COUNT:
                set_led_count(*(++inst));
                break;
        }
        ++inst;
    }

    return 0;
}

