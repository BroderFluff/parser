#ifndef CMD_PARSE_H__
#define CMD_PARSE_H__

#include "lexer.h"

enum cmd_type {
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
    CMD_ADD_ANIMATION_STARFALL,
    CMD_ADD_ANIMATION_START_LOOP,
    CMD_ADD_ANIMATION_END_LOOP,
    NUM_CMDS,
};

struct cmd_desc {
    enum cmd_type               cmd_type;
    const char *                name;
    int                         num_params;
};

//extern const struct cmd_desc    cmd_descs[];

int                     parse_next_inst(struct lexer *lex, int *inst_base);

const struct cmd_desc *         parse_get_cmd(enum cmd_type type);
struct cmd *                    parse_next_command(struct lexer *lex);

#endif // CMD_PARSE_H__
