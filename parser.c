#include <stdlib.h>
#include <string.h>

#include "parser.h"

PPARSER Parser_Create(PLINKED_LIST pTokens) {
    PPARSER pParser = malloc(sizeof(PARSER));
    if(pParser == NULL) {
        return NULL;
    }

    pParser->pTokens = pTokens;
    pParser->pCurrentToken = (PTOKEN)pTokens->pData;
    return pParser;
}

VOID __Parser_Advance(PPARSER pParser) {
    if(pParser->pTokens->pNext != NULL) {
        pParser->pTokens = pParser->pTokens->pNext;
        pParser->pCurrentToken = (PTOKEN)(pParser->pTokens->pData);
    }
}

PNODE Parser_Parse(PPARSER pParser) {
    return Parser_ParseExpression(pParser);
}

PNODE Parser_ParseValue(PPARSER pParser) {
    PTOKEN pCurrentToken = pParser->pCurrentToken;
    if(pCurrentToken->type == TokenTypeFloat || \
       pCurrentToken->type == TokenTypeInteger) {
           PNODE pNode = Node_CreateValue(pCurrentToken);
           __Parser_Advance(pParser);
           return pNode;
    }

    return NULL;
}

BOOL __char_in_str(CHAR c, PCHAR szString) {
    SIZE_T cszLength = strlen(szString);
    for(int i = 0; i < cszLength; i++) {
        if(szString[i] == c) {
            return TRUE;
        }
    }
    return FALSE;
}

PNODE Node_CreateBinaryOperation(PTOKEN pOperatorToken, PNODE pLeft, PNODE pRight) {
    PNODE pNode = malloc(sizeof(NODE));
    if(pNode == NULL) {
        return NULL;
    }

    pNode->pToken = pOperatorToken;
    pNode->type = NodeTypeBinaryOperation;
    pNode->pLeft = pLeft;
    pNode->pRight = pRight;
    return pNode;
}

PNODE Node_CreateValue(PTOKEN pOperatorToken) {
    PNODE pNode = malloc(sizeof(NODE));
    if(pNode == NULL) {
        return NULL;
    }

    pNode->pToken = pOperatorToken;
    pNode->type = NodeTypeValue;
    pNode->pLeft = NULL;
    pNode->pRight = NULL;
    return pNode;
}

PNODE Parser_ParseProduct(PPARSER pParser) {
    return Parser_ParseBinaryOperation(pParser, Parser_ParseValue, "*/");
}

PNODE Parser_ParseExpression(PPARSER pParser) {
    return Parser_ParseBinaryOperation(pParser, Parser_ParseProduct, "+-");
}

PNODE Parser_ParseBinaryOperation(PPARSER pParser, ParserBinaryOperationProc fnBinaryOperation, PCHAR symbols) {
    PNODE pLeft = fnBinaryOperation(pParser);
    while(TRUE) {
        PTOKEN pCurrentToken = pParser->pCurrentToken;
        if(pCurrentToken->type != TokenTypeSymbol) {
            break;
        } else if(!__char_in_str(pCurrentToken->u.cSymbol, symbols)) {
            break;
        }

        __Parser_Advance(pParser);
        PNODE pRight = fnBinaryOperation(pParser);
        pLeft = Node_CreateBinaryOperation(pCurrentToken, pLeft, pRight);
    }

    return pLeft;
}