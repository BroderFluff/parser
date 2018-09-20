#ifndef LEXER_H__
#define LEXER_H__

#include <assert.h>
#include <string.h>

#define TOKEN_MAX_LENGTH 32

enum token_type {
    TT_NONE,
    TT_NAME,
    TT_INTEGER,
};

/**
 * A string token produced by lexer
 */
struct token;

const char *        token_as_name(const struct token *tok);
int                 token_as_integer(const struct token *tok);

/**
 * Holds lexer-state for parser
 */
struct lexer;

int                 lexer_init_str(struct lexer *lex, const char *str);
static inline int   lexer_is_eof(const struct lexer *lex) { return lex->c && (*lex->c == '\0'); }
int                 lexer_next_token(struct lexer *lex, struct token *tok);

#endif // LEXER_H__