#ifndef LEXER_H__
#define LEXER_H__

#include "token.h"

/**
 * Holds lexer-state for parser
 */
struct lexer;

struct lexer *      lexer_alloc();
void                lexer_free(struct lexer *lex);
int                 lexer_init_str(struct lexer *lex, const char *str);
int                 lexer_is_eof(const struct lexer *lex);
int                 lexer_next_token(struct lexer *lex, struct token *tok);

#endif // LEXER_H__