#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

const char *token_as_name(const struct token *tok)
{
    assert(tok->type == TT_NAME);
    return tok->str;
}

int token_as_integer(const struct token *tok)
{
    assert(tok->type == TT_INTEGER);
    return strtol(tok->str, NULL, 10);
}

static int skip_spaces(const char **c)
{
    const char *start = *c;
    while (*c && isspace(*c)) {
        ++(*c);
    }
    return start - *c;
}

static int read_name(struct lexer *lex, struct token *tok)
{
    tok->len = 0;
    while (lex->c && isalpha(lex->c)) {
        tok->str[tok->len++] = *lex->c;
        ++(lex->c);
    }
    tok->str[tok->len] = '\0';
    tok->type = TT_NAME;
    return 0;
}

static int read_number(struct lexer *lex, struct token *tok)
{
    tok->len = 0;
    while (lex->c && isdigit(lex->c)) {
        lex->str[tok->len++] = *lex->c;
        ++(lex->c);
    }
}

int next_token(struct lexer *lex, struct token *tok)
{
    skip_spaces(&lex->c);
    if (is_eof(lex)) {
        return -1;
    }
    if (isalpha(lex->c)) {
        return read_name(lex, tok);
    } else if (isdigit(lex->c)) {
        return read_number(lex, tok);
    }

    return 0;
}
