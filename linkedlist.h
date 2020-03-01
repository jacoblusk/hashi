#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "types.h"

typedef struct tagLINKED_LIST LINKED_LIST, * PLINKED_LIST, ** PPLINKED_LIST;
struct tagLINKED_LIST {
    PLINKED_LIST pNext;
    LPVOID pData;
};

typedef void (*LinkedListDeallocatorProc)(PVOID);

PLINKED_LIST LinkedList_Prepend(PPLINKED_LIST ppLinkedList, LPVOID pData);
PLINKED_LIST LinkedList_Append(PPLINKED_LIST ppLinkedList, LPVOID pData);
VOID LinkedList_Destroy(PLINKED_LIST pTokenList, LinkedListDeallocatorProc fnLinkedListDeallocator);

#endif