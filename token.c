#include "token.h"
#include <stdlib.h>

struct token {
    enum token_type type;
    char            str[TOKEN_MAX_LENGTH];
    int             len;
};

struct token* token_alloc()
{
    struct token *tok = (struct token *) malloc(sizeof (struct token));
    return tok;
}

void token_free(struct token *tok)
{
    if (!tok) {
        return;
    }
    free(tok);
}

static void token_clear(struct token *tok)
{
    tok->type = TT_NONE;
    tok->str[0] = '\0';
    tok->len = 0;
}

const char *token_get_name(const struct token *tok)
{
    assert(tok->type == TT_NAME);
    return tok->str;
}

int token_get_integer(const struct token *tok)
{
    assert(tok->type == TT_INTEGER);
    return strtol(tok->str, NULL, 10);
}

