#ifndef DOUBLECIRCULARLINKEDLIST_H
#define DOUBLECIRCULARLINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define DOUBLECIRCULARLINKEDLIST_INIT_ERROR \
    "DoubleCircularLinkedListInitError: Failed to allocate memory\n"

#define DOUBLECIRCULARLINKEDLIST_ACCESS_ERROR \
    "DoubleCircularLinkedListAccessError: "\
    "Please check whether the `DoubleCircularLinkedList` type parameter is passed\n"

#define DOUBLECIRCULARLINKEDLIST_OVERFLOW_EXCEPTION \
    "DoubleCircularLinkedListOverFlowException: Exceed capacity limit\n"

#define DOUBLECIRCULARLINKEDLIST_NODE_INIT_ERROR \
    "DoubleCircularLinkedListNodeInitError: Failed to allocate memory\n"

#define DOUBLECIRCULARLINKEDLIST_INSERT_EXCEPTION \
    "DoubleCircularLinkedListInsertException: Index overshoot\n"

#define DOUBLECIRCULARLINKEDLIST_SEARCH_EXCEPTION \
    "DoubleCircularLinkedListSearchException: Specific element not found\n"

#define DOUBLECIRCULARLINKEDLIST_SEARCH_MODE_ERROR \
    "DoubleCircularLinkedListSearchException: Search mode error\n"

#define DOUBLECIRCULARLINKEDLIST_CHECK_ERROR \
    "DoubleCircularLinkedListCheckError: "\
    "The parameter is incorrect or the data in `DoubleCircularLinkedList` is empty\n"
    
#define DOUBLECIRCULARLINKEDLIST_REMOVE_EXCEPTION \
    "DoubleCircularLinkedListRemoveException: Search mode error or invalid parameter\n"

#define DOUBLECIRCULARLINKEDLIST_SEARCH_BY_POS 0

#define DOUBLECIRCULARLINKEDLIST_SEARCH_BY_VALUE 1


typedef int DoubleCircularLinkedListEleType;


typedef struct DoubleCircularLinkedListNode {
    DoubleCircularLinkedListEleType data;
    struct DoubleCircularLinkedListNode* prev;
    struct DoubleCircularLinkedListNode* next;
} DoubleCircularLinkedListNode;


typedef struct DoubleCircularLinkedList {
    DoubleCircularLinkedListNode* head;
    size_t length;
    ssize_t size;
} DoubleCircularLinkedList;


int doublecircularlinkedlist_push_front(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data);

int doublecircularlinkedlist_push_back(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data);

int doublecircularlinkedlist_insert(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data, size_t pos);

int doublecircularlinkedlist_remove(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data, size_t* pos, int mode);

int doublecircularlinkedlist_search(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data, size_t* pos, int mode);

int doublecircularlinkedlist_pop_front(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data);

int doublecircularlinkedlist_pop_back(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data);

int doublecircularlinkedlist_front(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data);

int doublecircularlinkedlist_back(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data);

int doublecircularlinkedlist_display(DoubleCircularLinkedList* list);

int doublecircularlinkedlist_clean(DoubleCircularLinkedList** list);

DoubleCircularLinkedList* 
doublecircularlinkedlist_create(ssize_t size, DoubleCircularLinkedListEleType init);

size_t doublecircularlinkedlist_length(DoubleCircularLinkedList* list);

ssize_t doublecircularlinkedlist_size(DoubleCircularLinkedList* list);

int _doublecircularlinkedlist_is_exceed_size(DoubleCircularLinkedList* list);

int doublecircularlinkedlist_is_empty(DoubleCircularLinkedList* list);

#endif // DOUBLECIRCULARLINKEDLIST_H
