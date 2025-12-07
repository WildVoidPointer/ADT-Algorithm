#ifndef SEQUENCE_LIST_H_
#define SEQUENCE_LIST_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define SEQUENCE_LIST_CREATE_ERROR \
    "SequenceListCreateError: Failed to allocate memory\n"


#define SEQUENCE_LIST_ELEMENTS_INIT_ERROR \
    "SequenceListElementsInitError: Failed to allocate memory\n"


#define SEQUENCE_LIST_EXPAND_ERROR \
    "SequenceListExpandError: Failed to reallocate memory\n"


#define SEQUENCE_LIST_ACCESS_EXCEPTION \
    "SequenceListAccessError: " \
    "Check whether parameter `SeqList*` is valid\n"


#define SEQUENCE_LIST_INSERT_EXCEPTION \
    "SequenceListInsertException: Index access is out of bounds\n"


#define SEQUENCE_LIST_REMOVE_EXCEPTION \
    "SequenceListRemoveException: Index access is out of bounds\n"


#define SEQUENCE_LIST_SEARCH_ACCESS_EXCEPTION \
    "SequenceListSearchAccessError: " \
    "Check whether parameter buffer is valid\n"


#define SEQUENCE_LIST_SEARCH_EXCEPTION_INDEX \
    "SequenceListSearchException: Index access is out of bounds\n"


#define SEQUENCE_LIST_SEARCH_NOT_FOUND \
    "SequenceListSearchException: Specific element not found\n"


typedef int SequenceListDataType;


typedef struct SequenceList {
    SequenceListDataType* elements;
    size_t length;
    size_t size;
} SequenceList;


SequenceList* SequenceList_create(size_t size);


int SequenceList_expand(SequenceList* seqlist, size_t expand_size);


size_t SequenceList_length(SequenceList* seqlist);


int SequenceList_is_empty(SequenceList* seqlist);


int SequenceList_insert(
    SequenceList* seqlist, size_t pos, SequenceListDataType buf
);


int SequenceList_remove(
    SequenceList* seqlist, size_t pos, SequenceListDataType* buf
);


int SequenceList_search(
    SequenceList* seqlist, size_t* pos, 
    SequenceListDataType* buf, int flag
);


int SequenceList_destroy(SequenceList** seqlist);


int SequenceList_display(SequenceList* seqlist);

#endif
