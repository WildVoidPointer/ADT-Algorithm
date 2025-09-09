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


#define SEQUENCE_LIST_ACCESS_ERROR \
    "SequenceListAccessError: Check whether parameter `SeqList*` is valid\n"


#define SEQUENCE_LIST_INSERT_EXCEPTION \
    "SequenceListInsertException: Index access is out of bounds\n"


#define SEQUENCE_LIST_REMOVE_EXCEPTION \
    "SequenceListRemoveException: Index access is out of bounds\n"


#define SEQUENCE_LIST_SEARCH_ACCESS_ERROR \
    "SequenceListSearchAccessError: Check whether parameter buffer is valid\n"


#define SEQUENCE_LIST_SEARCH_EXCEPTION_INDEX \
    "SequenceListSearchException: Index access is out of bounds\n"


#define SEQUENCE_LIST_SEARCH_NOT_FOUND \
    "SequenceListSearchException: Specific element not found\n"


typedef int SequenceListEleType;


typedef enum SequenceListInitModeEnum {
    SEQUENCE_LIST_INIT_DISABLE = 0,
    SEQUENCE_LIST_INIT_ENABLE = 1
} SequenceListInitModeEnum;


typedef struct SequenceList {
    SequenceListEleType* elements;
    SequenceListEleType init_data;
    size_t length;
    size_t size;
    int is_init;
} SequenceList;


SequenceList* SequenceList_create(
    size_t size, SequenceListInitModeEnum is_init, 
    SequenceListEleType *init_data
);


int SequenceList_expand(
    SequenceList* seqlist, size_t expand_size, 
    SequenceListInitModeEnum is_init
);


size_t SequenceList_length(SequenceList* seqlist);


int SequenceList_is_empty(SequenceList* seqlist);


int SequenceList_insert(
    SequenceList* seqlist, size_t pos, SequenceListEleType buf
);


int SequenceList_remove(
    SequenceList* seqlist, size_t pos, SequenceListEleType* buf
);


int SequenceList_search(
    SequenceList* seqlist, size_t* pos, 
    SequenceListEleType* buf, int flag
);


int SequenceList_clean(SequenceList** seqlist);


int SequenceList_display(SequenceList* seqlist);

#endif
