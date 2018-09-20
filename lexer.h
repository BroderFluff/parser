#define TOKEN_MAX_LENGTH 32

enum token_type {
    TT_NAME,
    TT_INTEGER,
};

struct token {
    enum token_type type;
    char            str[TOKEN_MAX_LENGTH];
    int             len;
};

struct lexer {
    char *          str;
    char *          c;
};

inline int is_eof(struct lexer *lex) { return (lex->c == '\0'); }
int next_token(struct lexer *lex, struct token *tok);


struct emptyCommand_t {

};