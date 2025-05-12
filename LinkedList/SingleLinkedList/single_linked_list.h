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

#define SINGLELINKEDLIST_SEARCH_BY_POS 0

#define SINGLELINKEDLIST_SEARCH_BY_VALUE 1


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


int singlelinkedlist_push_front(SingleLinkedList* list, SingleLinkedListEleType data);

int singlelinkedlist_push_back(SingleLinkedList* list, SingleLinkedListEleType data);

int singlelinkedlist_insert(SingleLinkedList* list, SingleLinkedListEleType data, size_t pos);

int singlelinkedlist_remove(SingleLinkedList* list, SingleLinkedListEleType* data, size_t pos, int mode);

int singlelinkedlist_search(SingleLinkedList* list, SingleLinkedListEleType* data, size_t* pos, int mode);

int singlelinkedlist_pop_front(SingleLinkedList* list, SingleLinkedListEleType* data);

int singlelinkedlist_pop_back(SingleLinkedList* list, SingleLinkedListEleType* data);

int singlelinkedlist_front(SingleLinkedList* list, SingleLinkedListEleType* data);

int singlelinkedlist_back(SingleLinkedList* list, SingleLinkedListEleType* data);

int singlelinkedlist_display(SingleLinkedList* list);

int singlelinkedlist_clean(SingleLinkedList** list);

SingleLinkedList* singlelinkedlist_create(ssize_t size);

size_t singlelinkedlist_length(SingleLinkedList* list);

ssize_t singlelinkedlist_size(SingleLinkedList* list);

int singlelinkedlist_is_empty(SingleLinkedList* list);

int _singlelinkedlist_is_exceed_size(SingleLinkedList* list);

#endif // SINGLELINKEDLIST_H
