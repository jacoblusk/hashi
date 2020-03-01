#include <string.h>
#include "token.h"

const char SYMBOLS[] = "!#$\%&'*+,-./:;<=>?@[\\]^_`{|}~";

BOOL issymbol(char c) {
    for(int i = 0; i < sizeof(SYMBOLS)/sizeof(CHAR); i++) {
        if(c == SYMBOLS[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

PTOKEN Token_CreateSymbol(CHAR cSymbol) {
    PTOKEN pToken = malloc(sizeof(TOKEN));
    if(pToken == NULL) {
        return NULL;
    }

    pToken->type = TokenTypeSymbol;
    pToken->u.cSymbol = cSymbol;
    return pToken;
}

PTOKEN Token_CreateLeftParenthesis(VOID) {
    PTOKEN pToken = malloc(sizeof(TOKEN));
    if(pToken == NULL) {
        return NULL;
    }

    pToken->type = TokenTypeLeftParenthesis;
    pToken->u.cSymbol = '(';
    return pToken;
}

PTOKEN Token_CreateRightParenthesis(VOID) {
    PTOKEN pToken = malloc(sizeof(TOKEN));
    if(pToken == NULL) {
        return NULL;
    }

    pToken->type = TokenTypeRightParenthesis;
    pToken->u.cSymbol = ')';
    return pToken;
}

PTOKEN Token_CreateInteger(UINT32 uInteger) {
    PTOKEN pToken = malloc(sizeof(TOKEN));
    if(pToken == NULL) {
        return NULL;
    }

    pToken->type = TokenTypeInteger;
    pToken->u.uInteger = uInteger;
    return pToken;
}

PTOKEN Token_CreateFloat(FLOAT fFloat) {
    PTOKEN pToken = malloc(sizeof(TOKEN));
    if(pToken == NULL) {
        return NULL;
    }

    pToken->type = TokenTypeFloat;
    pToken->u.fFloat = fFloat;
    return pToken;
}

VOID Token_Destroy(PTOKEN pToken) {
    memset(pToken, 0, sizeof(TOKEN));
    free(pToken);
}