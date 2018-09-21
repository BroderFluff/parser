#include "cmd_parse.h"
#include "lexer.h"
#include "token.h"
#include <string.h>
#include <stdio.h>

#define MAX_NUM_COMMANDS    256

struct command              command_pool[MAX_NUM_COMMANDS];
static int                  num_alloced = 0;

static struct command *command_alloc(enum command_type type)
{
    struct command *    cmd = &command_pool[num_alloced++];
    num_alloced %= MAX_NUM_COMMANDS;
    cmd->type = type;
    cmd->num_params = 0;
    return cmd;
}

static void command_add_param(struct command *cmd, int param)
{
    cmd->params[cmd->num_params++] = param;
}

static struct command* parse_set_led_count(struct lexer *lex)
{
    struct command *    cmd = NULL;
    struct token        tok;

    cmd = command_alloc(CMD_SET_LED_COUNT);

    if (!lexer_expect_type(lex, &tok, TT_INTEGER)) {
        printf("Parse error: Expected command param but found \"%s\"\n", tok.str);
        return NULL;
    }

    command_add_param(cmd, token_get_integer(&tok));
    return cmd;
}

static struct command* parse_set_led_positions(struct lexer *lex)
{
    return NULL;
}

static struct command* parse_clear_led_positions(struct lexer *lex)
{
    return NULL;
}

struct command* parse_next_command(struct lexer *lex)
{
    struct token tok;
    if (!lexer_expect_type(lex, &tok, TT_NAME)) {
        printf("Expected command name..");
        return NULL;
    }
    
    const char *cmd_name = token_get_name(&tok);
    if (strcmp(cmd_name, "setLEDCount") == 0) {
        return parse_set_led_count(lex);
    } else if (strcmp(cmd_name, "setLEDPositions") == 0) {
        return parse_set_led_positions(lex);
    } else if (strcmp(cmd_name, "clearLEDPositions") == 0) {
        return parse_clear_led_positions(lex);
    }

    return NULL;
}
