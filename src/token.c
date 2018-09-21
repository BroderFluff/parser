#include "token.h"
#include <assert.h>
#include <stdlib.h>

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

void token_clear(struct token *tok)
{
    tok->type = TT_NONE;
    tok->str[0] = '\0';
    tok->len = 0;
}

void token_append_char(struct token *tok, int ch)
{
    if (tok->len >= TOKEN_MAX_LENGTH) {
        return;
    }
    tok->str[tok->len++] = ch;
}

void token_finish(struct token *tok, enum token_type type)
{
    tok->str[tok->len] = '\0';
    tok->type = type;
}

enum token_type token_get_type(const struct token *tok)
{
    return tok->type;
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

