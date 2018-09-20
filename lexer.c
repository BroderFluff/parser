#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

#define VALIDATE_LEXER(lex) \
    assert(lex->c);

struct lexer {
    // Points to current position in str
    const char *    c;
    // Points to string currently being read
    const char *    str;
    int             line;
};

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

struct lexer* lexer_alloc()
{
    struct lexer *lex = malloc(sizeof (struct lexer));
    return lex;
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
