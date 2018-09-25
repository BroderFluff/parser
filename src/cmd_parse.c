#include "cmd_parse.h"
#include "lexer.h"
#include "token.h"
#include <string.h>
#include <stdio.h>

#define MAX_NUM_COMMANDS    256

const struct cmd_desc cmd_descs[] = {
    { CMD_SET_DEBUG, "setDebug", 0 },
    { CMD_GET_VERSION_NUMBER, "getVersionNumber", 0 },
    { CMD_SET_LED_COUNT, "setLEDCount", 1 },
    { CMD_SET_LED_POSITIONS, "setLEDPositions", 1 },
    { CMD_CLEAR_LED_POSITIONS, "clearLEDPositions", 0 },
    { CMD_CLEAR_ANIMATION_STACK, "clearAnimationStack", 0 },
    { CMD_ADD_ANIMATION_COLOR_WIPE, "addAnimationColorWipe", 3 },
    { CMD_ADD_ANIMATION_FADE_TO_COLOR, "addAnimationFadeToColor", 3 },
    { CMD_ADD_ANIMATION_DELAY_MS, "addAnimationDelayMS", 1 },
    { CMD_ADD_ANIMATION_DELAY_S, "addAnimationDelayS", 1 },
    { CMD_ADD_ANIMATION_SOLID_COLOR, "addAnimationSolidColor", 3 },
    { CMD_ADD_ANIMATION_STARFALL, "addAnimationStarfall", 0 },
    { CMD_ADD_ANIMATION_START_LOOP, "addAnimationStartLoop", 0 },
    { CMD_ADD_ANIMATION_END_LOOP, "addAnimationEndLoop", 0 },
};

int parse_next_inst(struct lexer *lex, int *inst) {
    if (!inst) {
        return 0;
    }

    struct token tok;
    if (lexer_expect_type(lex, &tok, TT_NAME)) {
        return 0;
    }

    int offset = 0;
    const char *cmd_name = token_get_name(&tok);
    for (int i = 0; i < NUM_CMDS; ++i) {
        if (strcmp(cmd_name, cmd_descs[i].name) == 0) {
            inst[offset++] = i;
            for (int j = 0; j < cmd_descs[i].num_params; ++j) {
                if (!lexer_expect_type(lex, &tok, TT_INTEGER)) {
                    return 0;
                }

            }
        }
    }

    return offset;
}

#if 0
int dparse_next_command(struct lexer *lex)
{
    struct token tok;
    if (!lexer_expect_type(lex, &tok, TT_NAME)) {
        printf("Expected command name..");
        return NULL;
    }

    enum cmd_type type;
    const char *cmd_name = token_get_name(&tok);
    for (int i = 0; i < NUM_CMDS; ++i) {
        if (strcmp(cmd_name, cmd_descs[i].name) == 0) {
            for (int i = 0; i < cmd_descs[i].num_params; ++i) {
                if (lexer_is_eof(lex)) {
                    printf("Unexpected end-of-file..");
                    return NULL;
                } else if (lexer_expect_type(lex, &tok, TT_INTEGER)) {
                    vm_add(token_get_integer(&tok));
                } else {
                    printf("Expected integer param..");
                    return NULL;
                }
            }
        }
    }

    return NULL;
}
#endif

/*static struct command *command_alloc(enum cmd_type type)
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
}*/

    /*if (strcmp(cmd_name, "setLEDCount") == 0) {
        return parse_set_led_count(lex);
    } else if (strcmp(cmd_name, "setLEDPositions") == 0) {
        return parse_set_led_positions(lex);
    } else if (strcmp(cmd_name, "clearLEDPositions") == 0) {
        return parse_clear_led_positions(lex);
    }*/

/*
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
*/
