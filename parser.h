#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "linkedlist.h"

typedef enum {
    NoneTypeUnknown,
    NodeTypeValue,
    NodeTypeBinaryOperation
} NODE_TYPE;

typedef struct tagNODE NODE, *PNODE;
struct tagNODE {
    NODE_TYPE type;
    PTOKEN pToken;
    PNODE pLeft;
    PNODE pRight;
};

typedef struct tagParser {
    PLINKED_LIST pTokens;
    PTOKEN pCurrentToken;
} PARSER, *PPARSER;

PPARSER Parser_Create(PLINKED_LIST pTokens);
PNODE Parser_Parse(PPARSER pParser);
PNODE Parser_ParseValue(PPARSER pParser);
PNODE Parser_ParseExpression(PPARSER pParser);
PNODE Node_CreateBinaryOperation(PTOKEN pOperatorToken, PNODE pLeft, PNODE pRight);
PNODE Node_CreateValue(PTOKEN pOperatorToken);

typedef PNODE (*ParserBinaryOperationProc)(PPARSER);
PNODE Parser_ParseBinaryOperation(PPARSER pParser, ParserBinaryOperationProc fnBinaryOperation, PCHAR symbols);

#endif