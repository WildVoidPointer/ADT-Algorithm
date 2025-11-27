#ifndef DC_LINKED_LIST_H_
#define DC_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define DC_LINKED_LIST_CREATE_ERROR \
    "DCLinkedListCreateError: Failed to allocate memory\n"


#define DC_LINKED_LIST_ACCESS_ERROR \
    "DCLinkedListAccessError: "\
    "Please check whether the `DCLinkedList` type parameter is passed\n"


#define DC_LINKED_LIST_OVERFLOW_EXCEPTION \
    "DCLinkedListOverFlowException: Exceed capacity limit\n"


#define DC_LINKED_LIST_NODE_INIT_ERROR \
    "DCLinkedListNodeInitError: Failed to allocate memory\n"


#define DC_LINKED_LIST_INSERT_EXCEPTION \
    "DCLinkedListInsertException: Index overshoot\n"


#define DC_LINKED_LIST_SEARCH_EXCEPTION \
    "DCLinkedListSearchException: Specific element not found\n"


#define DC_LINKED_LIST_SEARCH_MODE_ERROR \
    "DCLinkedListSearchException: Search mode error\n"


#define DC_LINKED_LIST_CHECK_ERROR \
    "DCLinkedListCheckError: " \
    "The parameter is incorrect or the data in " \
    "`DCLinkedList` is empty\n"
    

#define DC_LINKED_LIST_REMOVE_EXCEPTION \
    "DCLinkedListRemoveException: " \
    "Search mode error or invalid parameter\n"

#define DC_LINKED_LIST_SEARCH_BY_POS 0

#define DC_LINKED_LIST_SEARCH_BY_VALUE 1


typedef int DCLinkedListDataType;


typedef struct DCLinkedListNode {
    DCLinkedListDataType data;
    struct DCLinkedListNode* prev;
    struct DCLinkedListNode* next;
} DCLinkedListNode;


typedef struct DCLinkedList {
    DCLinkedListNode* head;
    size_t length;
    ssize_t size;
} DCLinkedList;


int DCLinkedList_push_front(
    DCLinkedList* list, 
    DCLinkedListDataType data
);

int DCLinkedList_push_back(
    DCLinkedList* list, 
    DCLinkedListDataType data
);

int DCLinkedList_insert(
    DCLinkedList* list, 
    DCLinkedListDataType data, 
    size_t pos
);

int DCLinkedList_remove(
    DCLinkedList* list, 
    DCLinkedListDataType* data, 
    size_t* pos, int mode
);

int DCLinkedList_search(
    DCLinkedList* list, 
    DCLinkedListDataType* data, 
    size_t* pos, int mode
);

int DCLinkedList_pop_front(
    DCLinkedList* list, 
    DCLinkedListDataType* data
);

int DCLinkedList_pop_back(
    DCLinkedList* list, 
    DCLinkedListDataType* data
);

int DCLinkedList_front(
    DCLinkedList* list, 
    DCLinkedListDataType* data
);

int DCLinkedList_back(
    DCLinkedList* list, 
    DCLinkedListDataType* data
);

int DCLinkedList_display(DCLinkedList* list);

int DCLinkedList_destroy(DCLinkedList** list);

DCLinkedList* DCLinkedList_create(
    ssize_t size, DCLinkedListDataType init
);

size_t DCLinkedList_length(DCLinkedList* list);

ssize_t DCLinkedList_size(DCLinkedList* list);

int _DCLinkedList_is_exceed_size(DCLinkedList* list);

int DCLinkedList_is_empty(DCLinkedList* list);

#endif // DOUBLECIRCULARLINKEDLIST_H
