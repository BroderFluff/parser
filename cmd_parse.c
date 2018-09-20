#include "cmd_parse.h"
#include "lexer.h"
#include "token.h"
#include <string.h>
#include <stdio.h>

#define MAX_NUM_COMMANDS 256

//static const int        MAX_NUM_COMMANDS = 256;

struct command          command_pool[MAX_NUM_COMMANDS];
static int              num_alloced = 0;

static struct command *alloc_command(enum command_type type)
{
    struct command *    cmd = &command_pool[num_alloced++];
    num_alloced %= MAX_NUM_COMMANDS;
    cmd->type = type;
    cmd->num_params = 0;
    return cmd;
}

static struct command* parse_set_led_count(struct lexer *lex)
{
    struct command *    cmd = NULL;
    struct token        tok;

    if (!lexer_expect_type(lex, &tok, TT_INTEGER)) {
        printf("Expected integer..\n");
        return NULL;
    }

    cmd = alloc_command(CMD_SET_LED_COUNT);
    cmd->params[cmd->num_params++] = token_get_integer(&tok);
    return cmd;
}

struct command* parse_next_command(struct lexer *lex)
{
    struct token tok;
    if (!lexer_expect_type(lex, &tok, TT_NAME)) {
        printf("Expected command name..");
        return NULL;
    }
    
    if (strcmp(token_get_name(&tok), "setLEDCount") == 0) {
        return parse_set_led_count(lex);
    }
    
    return NULL;
}





