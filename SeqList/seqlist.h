#ifndef SEQLIST_H
#define SEQLIST_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif

#define INIT_DATA 0

// 异常消息定义
#define SEQLIST_INIT_ERROR "SeqListInitError: Failed to allocate memory\n"
#define ELEMENTS_INIT_ERROR "ElementsInitError: Failed to allocate memory\n"
#define SEQLIST_ACCESS_ERROR "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"
#define SEQLIST_INSERT_EXCEPTION "SeqListInsertException: Index access is out of bounds\n"
#define SEQLIST_REMOVE_EXCEPTION "SeqListRemoveException: Index access is out of bounds\n"
#define SEQLIST_SEARCH_ACCESS_ERROR "SeqListSearchAccessError: Check whether parameter buffer is valid\n"
#define SEQLIST_SEARCH_EXCEPTION_INDEX "SeqListSearchException: Index access is out of bounds\n"
#define SEQLIST_SEARCH_EXCEPTION_NOT_FOUND "SeqListSearchException: Specific element not found\n"

typedef int SeqListEleType;

typedef struct SeqList {
    SeqListEleType* elements;
    size_t length;
    size_t size;
} SeqList;

SeqList* seqlist_create(size_t size);
size_t seqlist_length(SeqList* seqlist);
int seqlist_is_empty(SeqList* seqlist);
int seqlist_insert(SeqList* seqlist, size_t pos, SeqListEleType buf);
int seqlist_remove(SeqList* seqlist, size_t pos, SeqListEleType* buf);
int seqlist_search(SeqList* seqlist, size_t* pos, SeqListEleType* buf, int flag);
int seqlist_clean(SeqList** seqlist);
int seqlist_display(SeqList* seqlist);

#endif // SEQLIST_H
