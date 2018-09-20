#include "lexer.h"

static int skip_spaces(char **c)
{
    const char *start = c;
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
        ++lex->c;
    }
    tok->str[tok->len] = '\0';
    tok->type = TT_NAME;
}

static int read_number(struct lexer *lex, struct token *tok)
{
    tok->len = 0;
    while (lex->c && isdigit(lex->c)) {

    }
}

int next_token(struct lexer *lex, struct token *tok)
{
    if (!lex->c) {
        return 0;
    }

    skip_spaces(&lex->c);
    if (isalpha(lex->c)) {
        return read_name(lex, *tok);
    }
}