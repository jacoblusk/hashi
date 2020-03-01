#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "lexer.h"

PLEXER_ERROR LexerError_Create(LEXER_ERROR_TYPE type, LEXER_POSITION start, LEXER_POSITION end) {
    PLEXER_ERROR pLexerError = malloc(sizeof(LEXER_ERROR));
    if(pLexerError == NULL) {
        return NULL;
    }

    pLexerError->type = type;
    pLexerError->start = start;
    pLexerError->end = end;

    return pLexerError;
}

LEXER_POSITION LexerPosition_Create(void) {
    LEXER_POSITION lexerPosition;

    lexerPosition.cszColumn = 0;
    lexerPosition.cszLineNumber = 0;
    lexerPosition.uPosition = 0;
    return lexerPosition;
}

LEXER_POSITION LexerPosition_Advance(LEXER_POSITION lexerPosition, CHAR c) {
    lexerPosition.uPosition++;
    lexerPosition.cszColumn++;

    if(c == '\n') {
        lexerPosition.cszLineNumber++;
        lexerPosition.cszColumn = 0;
    }

    return lexerPosition;
}

PLEXER Lexer_Create(PCHAR pszText) {
    PLEXER pLexer = malloc(sizeof(LEXER));
    if(pLexer == NULL) {
        return NULL;
    }

    pLexer->pszText = pszText;
    pLexer->uLength = strlen(pszText);
    pLexer->position = LexerPosition_Create();

    return pLexer;
}

void Lexer_Destroy(PLEXER pLexer) {
    memset(pLexer, 0, sizeof(LEXER));
    free(pLexer);
}

char Lexer_CurrentCharacter(PLEXER pLexer) {
    return pLexer->pszText[pLexer->position.uPosition];
}

void __Lexer_Advance(PLEXER pLexer) {
    if(pLexer->position.uPosition < pLexer->uLength) {
        pLexer->position = LexerPosition_Advance(pLexer->position,
            Lexer_CurrentCharacter(pLexer));
    }
}

PTOKEN __Lexer_LexNumber(PLEXER pLexer) {
    LEXER_POSITION start = pLexer->position;
    SIZE_T cDotCount = 0;

    __Lexer_Advance(pLexer);
    while(TRUE) {
        CHAR cCurrent = Lexer_CurrentCharacter(pLexer);
        if(cCurrent == '.') {
            if(cDotCount > 0) {
                break;
            } else {
                cDotCount++;
            }
        } else if(!isdigit(cCurrent)) {
            break;
        }
        __Lexer_Advance(pLexer);
    }

    SIZE_T cLexemeLength = pLexer->position.uPosition - start.uPosition;
    PCHAR pszCopy = malloc(sizeof(char) * cLexemeLength + 1);
    if(pszCopy == NULL) {
        return NULL;
    }

    memcpy(pszCopy, pLexer->pszText + start.uPosition, cLexemeLength);
    pszCopy[cLexemeLength] = '\0';

    PTOKEN pToken = NULL;
    if(cDotCount == 0) {
        UINT32 uInteger = strtol(pszCopy, NULL, 10);
        pToken = Token_Create(uInteger);
    } else {
        float fFloat = strtof(pszCopy, NULL);
        pToken = Token_Create(fFloat);
    }

    free(pszCopy);
    return pToken;
}

PLEXER_ERROR Lexer_Lex(PLEXER pLexer, PPLINKED_LIST ppTokens) {
    CHAR cCurrent;
    while((cCurrent = Lexer_CurrentCharacter(pLexer)) != '\0') {
        if(isspace(cCurrent)) {
            __Lexer_Advance(pLexer);
        } else if(issymbol(cCurrent)) {
            PTOKEN pToken = Token_Create(cCurrent);
            LinkedList_Append(ppTokens, pToken);
            __Lexer_Advance(pLexer);
        } else if(isdigit(cCurrent)) {
            PTOKEN pToken = __Lexer_LexNumber(pLexer);
            LinkedList_Append(ppTokens, pToken);
        } else if(cCurrent == '(' || cCurrent == ')') {
            PTOKEN pToken = cCurrent == '(' ? Token_CreateLeftParenthesis() : Token_CreateRightParenthesis();
            LinkedList_Append(ppTokens, pToken);
            __Lexer_Advance(pLexer);
        } else {
            PLEXER_ERROR pLexerError = LexerError_Create(LexerErrorIllegalCharacter, pLexer->position, pLexer->position);
            if(pLexerError == NULL) {
                return NULL;
            }
            return pLexerError;
        }
    }

    return NULL;
}