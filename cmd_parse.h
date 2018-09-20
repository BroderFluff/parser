#ifndef CMD_PARSE_H__
#define CMD_PARSE_H__

#include "lexer.h"

//#define MAX_NUM_COMMANDS 256

enum command_type {
    CMD_SET_DEBUG,
    CMD_GET_VERSION_NUMBER,
    CMD_SET_LED_COUNT,
    CMD_SET_LED_POSITIONS,
    CMD_CLEAR_LED_POSITIONS,
    CMD_CLEAR_ANIMATION_STACK,
    CMD_ADD_ANIMATION_COLOR_WIPE,
    CMD_ADD_ANIMATION_FADE_TO_COLOR,
    CMD_ADD_ANIMATION_DELAY_MS,
    CMD_ADD_ANIMATION_DELAY_S,
    CMD_ADD_ANIMATION_SOLID_COLOR,
    CMD_ADD_ANIMATION_START_LOOP,
    CMD_ADD_ANIMATION_END_LOOP,
};

struct command {
    enum command_type       type;
    int                     num_params;
    int                     params[];
};

struct command *            parse_next_command(struct lexer *lex);

struct command_queue {
    int                     num_commands;
    struct command          commands[];
};

#endif // CMD_PARSE_H__
