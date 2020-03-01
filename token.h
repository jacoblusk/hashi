#ifndef TOKEN_H
#define TOKEN_H

#include "types.h"

typedef enum {
    TokenTypeUnknown = 0,
    TokenTypeInteger = 1,
    TokenTypeFloat = 2,
    TokenTypeString = 3,
    TokenTypeSymbol = 4,
    TokenTypeIdentifier = 5,
    TokenTypeLeftParenthesis = 6,
    TokenTypeRightParenthesis = 7
} LEXER_TOKEN_TYPE;

typedef struct {
    LEXER_TOKEN_TYPE type;
    union {
        PCHAR pszString;
        float fFloat;
        CHAR cSymbol;
        UINT32 uInteger;
    } u;
} TOKEN, *PTOKEN, **PPTOKEN;

BOOL issymbol(char c);

PTOKEN Token_CreateSymbol(CHAR cSymbol);
PTOKEN Token_CreateLeftParenthesis(VOID);
PTOKEN Token_CreateRightParenthesis(VOID);
PTOKEN Token_CreateInteger(UINT32 uInteger);
PTOKEN Token_CreateFloat(FLOAT fFloat);
VOID Token_Destroy(PTOKEN pToken);

#define Token_Create(X) _Generic((X), \
              CHAR:   Token_CreateSymbol, \
              UINT32: Token_CreateInteger,  \
              FLOAT:  Token_CreateFloat  \
)(X)

#endif