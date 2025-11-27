#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define S_LINKED_LIST_INIT_ERROR \
    "SLinkedListInitError: Failed to allocate memory\n"


#define S_LINKED_LIST_ACCESS_ERROR \
    "SLinkedListAccessError: " \
    "Please check whether the `SLinkedList` type parameter is passed\n"


#define S_LINKED_LIST_OVERFLOW_EXCEPTION \
    "SLinkedListOverFlowException: Exceed capacity limit\n"


#define S_LINKED_LIST_NODE_INIT_ERROR \
    "SLinkedListNodeInitError: Failed to allocate memory\n"

#define S_LINKED_LIST_INSERT_EXCEPTION \
    "SLinkedListInsertException: Index overshoot\n"

#define S_LINKED_LIST_SEARCH_EXCEPTION \
    "SLinkedListSearchException: Specific element not found\n"

#define S_LINKED_LIST_SEARCH_MODE_ERROR \
    "SLinkedListSearchException: Search mode error\n"

#define S_LINKED_LIST_CHECK_ERROR \
    "SLinkedListCheckError: " \
    "The parameter is incorrect or the data in `SLinkedList` is empty\n"


#define S_LINKED_LIST_REMOVE_EXCEPTION \
    "SLinkedListRemoveException: Search mode error or invalid parameter\n"


typedef enum SLinkedListSearchModeEnum {
    S_LINKED_LIST_SEARCH_BY_POS,
    S_LINKED_LIST_SEARCH_BY_VALUE
} SLinkedListSearchModeEnum;


typedef int SLinkedListDataType;


typedef struct SLinkedListNode {
    SLinkedListDataType data;
    struct SLinkedListNode* next;
} SLinkedListNode;


typedef struct SLinkedList {
    SLinkedListNode* head;
    size_t length;
    ssize_t size;
} SLinkedList;


SLinkedList* SLinkedList_create(ssize_t size);

int SLinkedList_push_front(
    SLinkedList* list, SLinkedListDataType data
);

int SLinkedList_push_back(
    SLinkedList* list, SLinkedListDataType data
);

int SLinkedList_insert(
    SLinkedList* list, 
    SLinkedListDataType data, 
    size_t pos
);

int SLinkedList_remove(
    SLinkedList* list, 
    SLinkedListDataType* data, 
    size_t pos, 
    SLinkedListSearchModeEnum mode
);


int SLinkedList_search(
    SLinkedList* list, 
    SLinkedListDataType* data, 
    size_t* pos, 
    SLinkedListSearchModeEnum mode
);

int SLinkedList_pop_front(
    SLinkedList* list, 
    SLinkedListDataType* data
);

int SLinkedList_pop_back(
    SLinkedList* list, 
    SLinkedListDataType* data
);

int SLinkedList_front(
    SLinkedList* list, 
    SLinkedListDataType* data
);

int SLinkedList_back(
    SLinkedList* list, 
    SLinkedListDataType* data
);

int SLinkedList_reverse(SLinkedList* list);

int SLinkedList_recursion_reverse(SLinkedList* list);

SLinkedListNode* 
_SLinkedList_recursion_reverse_node(SLinkedListNode* node);

int SLinkedList_display(SLinkedList* list);

int SLinkedList_clean(SLinkedList** list);

size_t SLinkedList_length(SLinkedList* list);

ssize_t SLinkedList_size(SLinkedList* list);

int SLinkedList_is_empty(SLinkedList* list);

int _SLinkedList_is_exceed_size(SLinkedList* list);

#endif // S_LINKED_LIST_H
