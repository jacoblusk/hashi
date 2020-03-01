#include "linkedlist.h"

PLINKED_LIST LinkedList_Prepend(PPLINKED_LIST ppLinkedList, LPVOID pData) {
    PLINKED_LIST pNewElement = malloc(sizeof(LINKED_LIST));
    if(pNewElement == NULL) {
        return NULL;
    }

    pNewElement->pData = pData;
    pNewElement->pNext = *ppLinkedList;

    *ppLinkedList = pNewElement;
    return pNewElement;
}

PLINKED_LIST LinkedList_Append(PPLINKED_LIST ppLinkedList, LPVOID pData) {
    PLINKED_LIST pNewElement = malloc(sizeof(LINKED_LIST));
    if(pNewElement == NULL) {
        return NULL;
    }

    pNewElement->pData = pData;
    pNewElement->pNext = NULL;

    if(*ppLinkedList == NULL) {
        *ppLinkedList = pNewElement;
        return pNewElement;
    }

    PLINKED_LIST pCurrent = *ppLinkedList;
    while(pCurrent->pNext != NULL) {
        pCurrent = pCurrent->pNext;
    }

    pCurrent->pNext = pNewElement;

    return pNewElement;
}

VOID LinkedList_Destroy(PLINKED_LIST pTokenList, LinkedListDeallocatorProc fnLinkedListDeallocator) {
    for(PLINKED_LIST pCurrent = pTokenList; pCurrent != NULL;) {
        PLINKED_LIST pNext = pCurrent->pNext;
        fnLinkedListDeallocator(pCurrent->pData);
        free(pCurrent);
        pCurrent = pNext;
    }
}