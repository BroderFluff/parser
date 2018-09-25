#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "token.h"
#include "lexer.h"

#ifdef DEBUG
#define VALIDATE_LEXER(lex) \
    assert(lex->c);
#else
#define VALIDATE_LEXER(lex) 
#endif

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
    return 1;
}

int lexer_is_eof(const struct lexer *lex)
{
    return lex->c && (*lex->c == '\0');
}

static long skip_spaces(struct lexer *lex)
{
    VALIDATE_LEXER(lex);
    const char *start = lex->c;
    while (!lexer_is_eof(lex) && 
            (isspace(*lex->c) > 0)) {
        if (*(lex->c) == '\n') {
            lex->line++;
        }
        ++(lex->c);
    }
    return lex->c - start;
}

/**
 *  Parses a TT_NAME from lex into tok.
 *  A name may only consist of alphanum-characters
 *  and start with a alpha.
 * 
 *  returns number of characters parsed
 */
static int read_name(struct lexer *lex, struct token *tok)
{
    token_clear(tok);

    while (!lexer_is_eof(lex) && isalnum(*lex->c)) {
        token_append_char(tok, *lex->c);
        ++lex->c;
    }

    token_finish(tok, TT_NAME);
    return tok->len;
}

/**
 *  Parses a TT_INTEGER from lex into tok.
 *  An integer may only consist of digits ('0' - '9').
 * 
 *  returns number of characters parsed
 */
static int read_number(struct lexer *lex, struct token *tok)
{
    token_clear(tok);

    while (!lexer_is_eof(lex) && isdigit(*lex->c)) {
        token_append_char(tok, *lex->c);
        ++lex->c;
    }

    token_finish(tok, TT_INTEGER);
    return tok->len;
}

/**
 *  Parses the next token available in lex, into tok.
 *  Skips spaces preceeding the token.
 * 
 *  returns number of characters parsed (spaces included)
 */
long lexer_next_token(struct lexer *lex, struct token *tok)
{
    assert(tok);
    VALIDATE_LEXER(lex);
    long num_ch = skip_spaces(lex);

    if (lexer_is_eof(lex)) {
        return 0;
    }

    if (isalpha(*(lex->c))) {
        num_ch += read_name(lex, tok);
    } else if (isdigit(*(lex->c))) {
        num_ch += read_number(lex, tok);
    } else {
        printf("Unknown token!\n");
    }
    
   // printf("read %ld chars : [%.*s\n", num_ch, (int) num_ch, lex->c - num_ch);
    return num_ch;
}

long lexer_expect_type(struct lexer *lex, struct token *tok, enum token_type type)
{
    long num_ch = lexer_next_token(lex, tok);
    if (num_ch > 0L) {
        if (tok->type != type) {
            printf("Expected \"%s\" but found \"%s\"\n", token_type_to_str(type), token_type_to_str(tok->type));
            return 0L;
        }
    }
    return num_ch;    
}
