#include "cmd_parse.h"
#include "lexer.h"
#include "token.h"
#include <string.h>
#include <stdio.h>

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

/**
 *  Parses next command and it's parameters.
 *  Will exit with an error if the parameter count
 *  doesnt match the spec or if the command is not recognized
 * 
 *  Returns the number of instructions generated
 */
size_t parse_next_command(struct lexer *lex, int *inst) {
    if (!inst) {
        return 0;
    }

    struct token tok;
    if (!lexer_expect_type(lex, &tok, TT_NAME)) {
        return 0;
    }

    size_t offset = 0;
    const char *cmd_name = token_get_name(&tok);
    for (int i = 0; i < NUM_CMDS; ++i) {
        if (strcmp(cmd_name, cmd_descs[i].name) == 0) {
            printf("Found token \"%s\"\n", tok.str);
            inst[offset++] = i;

            for (int j = 0; j < cmd_descs[i].num_params; ++j) {
                if (!lexer_expect_type(lex, &tok, TT_INTEGER)) {
                    return (size_t)-1;
                }
                inst[offset++] = token_get_integer(&tok);
            }
        }
    }

    return offset;
}
