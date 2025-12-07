#include "sequence_list.h"


SequenceList* SequenceList_create(size_t size) {

    SequenceList* seqlist = (SequenceList*)malloc(sizeof(SequenceList));
    if (seqlist == NULL) {
        fprintf(stderr, SEQUENCE_LIST_CREATE_ERROR);
        return NULL;
    }

    seqlist->elements = (SequenceListDataType*) malloc(
        size * sizeof(SequenceListDataType)
    );
    if (seqlist->elements == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ELEMENTS_INIT_ERROR);
        free(seqlist);
        return NULL;
    }
    
    seqlist->size = size;
    seqlist->length = 0;
    return seqlist;
}


int SequenceList_expand(SequenceList* seqlist, size_t expand_size) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ACCESS_EXCEPTION);
        return -1;
    }

    SequenceListDataType* tmp = (SequenceListDataType*) 
        realloc (
            seqlist->elements, 
            sizeof(SequenceListDataType) * (seqlist->size + expand_size)
        );

    if (tmp == NULL) {
        fprintf(stderr, SEQUENCE_LIST_EXPAND_ERROR);
        return -1;
    } else {
        seqlist->elements = tmp;
    }

    seqlist->size = seqlist->size + expand_size;
    return 0;
}


size_t SequenceList_length(SequenceList* seqlist) {
    return seqlist->length;
}


int SequenceList_is_empty(SequenceList* seqlist) {
    return seqlist->length == 0 ? 1 : 0;
}


int SequenceList_insert(SequenceList* seqlist, size_t pos, SequenceListDataType buf) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ACCESS_EXCEPTION);
        return -1;
    }

    if (seqlist->length == 0) {
        seqlist->elements[seqlist->length] = buf;
    } else {
        if (pos <= 0 || pos > seqlist->length + 1 || seqlist->length >= seqlist->size) {
            fprintf(stderr, SEQUENCE_LIST_INSERT_EXCEPTION);
            return -1;
        }

        for (size_t i = seqlist->length; i > pos - 1; i--) {
            seqlist->elements[i] = seqlist->elements[i - 1];
        }

        seqlist->elements[pos - 1] = buf;
    }

    seqlist->length++;
    return 0;
}


int SequenceList_remove(SequenceList* seqlist, size_t pos, SequenceListDataType* buf) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ACCESS_EXCEPTION);
        return -1;
    }

    if (seqlist->length == 0 || pos > seqlist->length || pos <= 0) {
        fprintf(stderr, SEQUENCE_LIST_REMOVE_EXCEPTION);
        return -1;
    }

    *buf = seqlist->elements[pos - 1];

    for (size_t i = pos - 1; i < seqlist->length - 1; i++) {
        seqlist->elements[i] = seqlist->elements[i + 1];
    }

    (seqlist->length)--;
    return 0;
}


int SequenceList_search(
    SequenceList* seqlist, size_t* pos, SequenceListDataType* buf, int flag
) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ACCESS_EXCEPTION);
        return -1;
    }

    if (pos == NULL || buf == NULL) {
        fprintf(stderr, SEQUENCE_LIST_SEARCH_ACCESS_EXCEPTION);
        return -1;
    }

    if (flag == 0) {
        if (seqlist->length == 0 || *pos > seqlist->length || *pos <= 0) {
            fprintf(stderr, SEQUENCE_LIST_SEARCH_EXCEPTION_INDEX);
            return -1;
        }
        *buf = seqlist->elements[*pos - 1];
    }
    else if (flag == -1) {
        int found_state = 0;
        for (size_t i = 0; i < seqlist->length; i++) {
            if (seqlist->elements[i] == *buf) {
                found_state = 1;
                *pos = i + 1;
                break;
            }
        }
        if (!found_state) {
            fprintf(stderr, SEQUENCE_LIST_SEARCH_NOT_FOUND);
            return -1;
        }
    }
    else {
        fprintf(stderr, SEQUENCE_LIST_SEARCH_EXCEPTION_INDEX);
        return -1;
    }
    return 0;
}


int SequenceList_destroy(SequenceList** seqlist) {
    if (seqlist == NULL || (*seqlist) == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ACCESS_EXCEPTION);
        return -1;
    }
    free((*seqlist)->elements);
    free(*seqlist);
    *seqlist = NULL;
    return 0;
}


int SequenceList_display(SequenceList* seqlist) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQUENCE_LIST_ACCESS_EXCEPTION);
        return -1;
    }

    printf("SeqList: {  ");
    for (size_t i = 0; i < seqlist->length; i++) {
        printf("%d  ", seqlist->elements[i]);
    }
    printf("}  length: %zu    size: %zu\n", seqlist->length, seqlist->size);

    return 0;
}
