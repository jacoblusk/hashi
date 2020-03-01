#ifndef LEXER_H
#define LEXER_H

#include "linkedlist.h"
#include "token.h"

typedef struct {
    SIZE_T uPosition;
    SIZE_T cszLineNumber;
    SIZE_T cszColumn;
} LEXER_POSITION;

typedef enum {
    LexerErrorIllegalCharacter
} LEXER_ERROR_TYPE;

typedef struct {
    LEXER_ERROR_TYPE type;
    LEXER_POSITION start;
    LEXER_POSITION end;
} LEXER_ERROR, *PLEXER_ERROR;

typedef struct {
    PCHAR pszText;
    SIZE_T uLength;
    LEXER_POSITION position;
} LEXER, *PLEXER, **PPLEXER;

PLEXER_ERROR LexerError_Create(LEXER_ERROR_TYPE type, LEXER_POSITION start, LEXER_POSITION end);
LEXER_POSITION LexerPosition_Create(void);
LEXER_POSITION LexerPosition_Advance(LEXER_POSITION lexerPosition, CHAR c);
PLEXER Lexer_Create(PCHAR pszText);
void Lexer_Destroy(PLEXER pLexer);
char Lexer_CurrentCharacter(PLEXER pLexer);
void __Lexer_Advance(PLEXER pLexer);
PTOKEN __Lexer_LexNumber(PLEXER pLexer);
PLEXER_ERROR Lexer_Lex(PLEXER pLexer, PPLINKED_LIST ppTokens);

#endif