#ifndef SEQLIST_H
#define SEQLIST_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif

#define SEQLIST_INIT_ERROR "SeqListInitError: Failed to allocate memory\n"

#define ELEMENTS_INIT_ERROR "ElementsInitError: Failed to allocate memory\n"

#define SEQLIST_ACCESS_ERROR \
    "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"

#define SEQLIST_INSERT_EXCEPTION \
    "SeqListInsertException: Index access is out of bounds\n"

#define SEQLIST_REMOVE_EXCEPTION \
    "SeqListRemoveException: Index access is out of bounds\n"

#define SEQLIST_SEARCH_ACCESS_ERROR \
    "SeqListSearchAccessError: Check whether parameter buffer is valid\n"

#define SEQLIST_SEARCH_EXCEPTION_INDEX \
    "SeqListSearchException: Index access is out of bounds\n"

#define SEQLIST_SEARCH_NOT_FOUND \
    "SeqListSearchException: Specific element not found\n"


typedef int SeqListEleType;


typedef enum SeqListInitModeEnum {
    SEQLIST_INIT_DISABLE,
    SEQLIST_INIT_ENABLE
} SeqListInitModeEnum;


typedef struct SeqList {
    SeqListEleType* elements;
    SeqListEleType init;
    size_t length;
    size_t size;
    int is_init;
} SeqList;


SeqList* 
SeqList_create(size_t size, SeqListInitModeEnum is_init, SeqListEleType *init_data);

size_t SeqList_length(SeqList* seqlist);

int SeqList_is_empty(SeqList* seqlist);

int SeqList_insert(SeqList* seqlist, size_t pos, SeqListEleType buf);

int SeqList_remove(SeqList* seqlist, size_t pos, SeqListEleType* buf);

int SeqList_search(SeqList* seqlist, size_t* pos, SeqListEleType* buf, int flag);

int SeqList_clean(SeqList** seqlist);

int SeqList_display(SeqList* seqlist);

#endif // SEQLIST_H
