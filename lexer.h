#ifndef LEXER_H__
#define LEXER_H__

#include <assert.h>
#include <string.h>

#define TOKEN_MAX_LENGTH 32

enum token_type {
    TT_NAME,
    TT_INTEGER,
};

/**
 * A string token produced by lexer
 */
struct token {
    enum token_type type;
    char            str[TOKEN_MAX_LENGTH];
    int             len;
};

const char *        token_as_name(const struct token *tok);
int                 token_as_integer(const struct token *tok);

/**
 * Holds lexer-state for parser
 */
struct lexer {
    char *          str;
    char *          c;
};

inline int          is_eof(struct lexer *lex) { return (*lex->c == '\0'); }
int                 next_token(struct lexer *lex, struct token *tok);

#endif // LEXER_H__