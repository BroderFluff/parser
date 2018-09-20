#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "token.h"
#include "lexer.h"

#define VALIDATE_LEXER(lex) \
    assert(lex->c);

struct lexer {
    // Points to current position in str
    const char *    c;
    // Points to string currently being read
    const char *    str;
    // Current line number
    int             line;
};

struct lexer* lexer_alloc()
{
    struct lexer *lex = malloc(sizeof (struct lexer));
    return lex;
}

void lexer_free(struct lexer *lex)
{
    if (!lex) {
        return;
    }
    free(lex);
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
        token_append_char(tok, *lex->c);
        ++(lex->c);
    }
    token_finish(tok, TT_NAME);
    return tok->len;
}

static int read_number(struct lexer *lex, struct token *tok)
{
    token_clear(tok);
    while (lex->c && isdigit(*lex->c)) {
        token_append_char(tok, *lex->c);
        ++(lex->c);
    }
    token_finish(tok, TT_INTEGER);
    return tok->len;
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

int lexer_expect_type(struct lexer *lex, struct token *tok, enum token_type type)
{
    int num = lexer_next_token(lex, tok);
    if (num > 0) {
        if (tok->type != type) {
            return 0;
        }
    }

    return num;    
}
