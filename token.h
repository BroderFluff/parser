#ifndef TOKEN_H__
#define TOKEN_H__

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

// Alloc token instance
struct token *      token_alloc();
// Free token instance
void                token_free(struct token *tok);
void token_clear(struct token *tok);
// Query token type
bool                token_is_type(const struct token *tok, enum token_type type);
// Return this token of name type
const char *        token_as_name(const struct token *tok);
// Return this token as integer
int                 token_as_integer(const struct token *tok);

#endif // TOKEN_H__
