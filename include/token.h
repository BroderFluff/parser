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
struct token {
    enum token_type type;
    char            str[TOKEN_MAX_LENGTH];
    int             len;
};

// Alloc token instance
struct token *      token_alloc();
// Free token instance
void                token_free(struct token *tok);
// Clear token contents
void                token_clear(struct token *tok);
// Append char to token
void                token_append_char(struct token *tok, int ch);
// Tidy up and set the token type of the token
void                token_finish(struct token *tok, enum token_type type);
// Query the token_type of token
enum token_type     token_get_type(const struct token *tok);
const char *        token_type_to_str(enum token_type type);
// Return this token of name type
const char *        token_get_name(const struct token *tok);
// Return this token as integer
int                 token_get_integer(const struct token *tok);

#endif // TOKEN_H__
