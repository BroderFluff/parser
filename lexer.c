#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

#define VALIDATE_LEXER(lex) \
    assert(lex->c);

struct token {
    enum token_type type;
    char            str[TOKEN_MAX_LENGTH];
    int             len;
};

struct lexer {
    // Points to current position in str
    const char *    c;
    // Points to string currently being read
    const char *    str;
    int             line;
};

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

static void token_clear(struct token *tok)
{
    tok->type = TT_NONE;
    tok->str[0] = '\0';
    tok->len = 0;
}

static int skip_spaces(struct lexer *lex)
{
    VALIDATE_LEXER(lex);
    const char *start = lex->c;
    while (!lexer_is_eof(lex) && 
            isspace(*lex->c)) {
        if (*(lex->c) == '\n') {
            lex->line++;
        }
        ++(lex->c);
    }
    return lex->c - start;
}

static int read_name(struct lexer *lex, struct token *tok)
{
    VALIDATE_LEXER(lex);
    token_clear(tok);
    while (!lexer_is_eof(lex) &&
            isalpha(*lex->c) ||
            isdigit(*lex->c)) {
        tok->str[tok->len++] = *lex->c;
        ++(lex->c);
    }
    tok->str[tok->len] = '\0';
    tok->type = TT_NAME;
    return 0;
}

static int read_number(struct lexer *lex, struct token *tok)
{
    token_clear(tok);
    while (lex->c && isdigit(*lex->c)) {
        tok->str[tok->len++] = *lex->c;
        ++(lex->c);
    }
    tok->str[tok->len] = '\0';
    tok->type = TT_INTEGER;
}

int lexer_init_str(struct lexer *lex, const char *str)
{
    lex->c = lex->str = str;
    lex->line = 1;
}

int lexer_is_eof(const struct lexer *lex)
{
    return lex->c && (*lex->c == '\0');
}

int lexer_next_token(struct lexer *lex, struct token *tok)
{
    skip_spaces(lex);

    if (lexer_is_eof(lex)) {
        return 0;
    }

    if (isalpha(*lex->c)) {
        return read_name(lex, tok);
    } else if (isdigit(*lex->c)) {
        return read_number(lex, tok);
    }

    return 0;
}
