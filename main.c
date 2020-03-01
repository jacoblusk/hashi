#define _UNICODE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "types.h"
#include "linkedlist.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv) {
    CHAR *test = "4+6.765*5";
    PLEXER pLexer = Lexer_Create(test);
    PLINKED_LIST pTokens = NULL;
    PLEXER_ERROR pLexerError = Lexer_Lex(pLexer, &pTokens);

    if(pLexerError == NULL) {
        for(PLINKED_LIST pCurrent = pTokens; pCurrent != NULL; pCurrent = pCurrent->pNext) {
            PTOKEN pToken = (PTOKEN)pCurrent->pData;
            switch(pToken->type) {
            case TokenTypeFloat:
                printf("[Float: %f]", ((PTOKEN)pCurrent->pData)->u.fFloat);
                break;
            case TokenTypeInteger:
                printf("[Integer: %d]", ((PTOKEN)pCurrent->pData)->u.uInteger);
                break;
            case TokenTypeSymbol:
                printf("[Symbol: %c]", ((PTOKEN)pCurrent->pData)->u.cSymbol);
                break;
            case TokenTypeLeftParenthesis:
            case TokenTypeRightParenthesis:
                printf("%c", ((PTOKEN)pCurrent->pData)->u.cSymbol);
                break;
            }

            if(pToken->type != TokenTypeLeftParenthesis && pToken->type != TokenTypeLeftParenthesis)
                printf(" ");
        }
        printf("\n");
    }

    PPARSER pParser = Parser_Create(pTokens);
    PNODE pAST = Parser_Parse(pParser);

    Lexer_Destroy(pLexer);
    LinkedList_Destroy(pTokens, (LinkedListDeallocatorProc)Token_Destroy);
    return EXIT_SUCCESS;
}