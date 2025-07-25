#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif

#define SINGLELINKEDLIST_INIT_ERROR "SingleLinkedListInitError: Failed to allocate memory\n"

#define SINGLELINKEDLIST_ACCESS_ERROR \
    "SingleLinkedListAccessError: Please check whether the `SingleLinkedList` type parameter is passed\n"

#define SINGLELINKEDLIST_OVERFLOW_EXCEPTION "SingleLinkedListOverFlowException: Exceed capacity limit\n"

#define SINGLELINKEDLIST_NODE_INIT_ERROR "SingleLinkedListNodeInitError: Failed to allocate memory\n"

#define SINGLELINKEDLIST_INSERT_EXCEPTION "SingleLinkedListInsertException: Index overshoot\n"

#define SINGLELINKEDLIST_SEARCH_EXCEPTION "SingleLinkedListSearchException: Specific element not found\n"

#define SINGLELINKEDLIST_SEARCH_MODE_ERROR "SingleLinkedListSearchException: Search mode error\n"

#define SINGLELINKEDLIST_CHECK_ERROR \
    "SingleLinkedListCheckError: The parameter is incorrect or the data in `SingleLinkedList` is empty\n"

#define SINGLELINKEDLIST_REMOVE_EXCEPTION \
    "SingleLinkedListRemoveException: Search mode error or invalid parameter\n"


typedef enum SingleLinkedListSearchModeEnum {
    SINGLELINKEDLIST_SEARCH_BY_POS,
    SINGLELINKEDLIST_SEARCH_BY_VALUE
} SingleLinkedListSearchModeEnum;


typedef int SingleLinkedListEleType;


typedef struct SingleLinkedListNode {
    SingleLinkedListEleType data;
    struct SingleLinkedListNode* next;
} SingleLinkedListNode;


typedef struct SingleLinkedList {
    SingleLinkedListNode* head;
    size_t length;
    ssize_t size;
} SingleLinkedList;


SingleLinkedList* SingleLinkedList_create(ssize_t size);

int SingleLinkedList_push_front(SingleLinkedList* list, SingleLinkedListEleType data);

int SingleLinkedList_push_back(SingleLinkedList* list, SingleLinkedListEleType data);

int SingleLinkedList_insert(SingleLinkedList* list, SingleLinkedListEleType data, size_t pos);

int SingleLinkedList_remove(
    SingleLinkedList* list, SingleLinkedListEleType* data, 
    size_t pos, SingleLinkedListSearchModeEnum mode);

int SingleLinkedList_search(
    SingleLinkedList* list, SingleLinkedListEleType* data, 
    size_t* pos, SingleLinkedListSearchModeEnum mode);

int SingleLinkedList_pop_front(SingleLinkedList* list, SingleLinkedListEleType* data);

int SingleLinkedList_pop_back(SingleLinkedList* list, SingleLinkedListEleType* data);

int SingleLinkedList_front(SingleLinkedList* list, SingleLinkedListEleType* data);

int SingleLinkedList_back(SingleLinkedList* list, SingleLinkedListEleType* data);

int SingleLinkedList_reverse(SingleLinkedList* list);

int
SingleLinkedList_recursion_reverse(SingleLinkedList* list);

SingleLinkedListNode* 
_SingleLinkedList_recursion_reverse_node(SingleLinkedListNode* node);

int SingleLinkedList_display(SingleLinkedList* list);

int SingleLinkedList_clean(SingleLinkedList** list);

size_t SingleLinkedList_length(SingleLinkedList* list);

ssize_t SingleLinkedList_size(SingleLinkedList* list);

int SingleLinkedList_is_empty(SingleLinkedList* list);

int _SingleLinkedList_is_exceed_size(SingleLinkedList* list);

#endif // SINGLELINKEDLIST_H
