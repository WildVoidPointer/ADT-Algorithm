#include "seqlist.h"

SeqList* seqlist_create(size_t size) {
    SeqList* seqlist = (SeqList*)malloc(sizeof(SeqList));
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_INIT_ERROR);
        return NULL;
    }

    seqlist->elements = (SeqListEleType*)malloc(size * sizeof(SeqListEleType));
    if (seqlist->elements == NULL) {
        fprintf(stderr, ELEMENTS_INIT_ERROR);
        free(seqlist);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        seqlist->elements[i] = INIT_DATA;
    }

    seqlist->size = size;
    seqlist->length = 0;
    return seqlist;
}


size_t seqlist_length(SeqList* seqlist) {
    return seqlist->length;
}


int seqlist_is_empty(SeqList* seqlist) {
    return seqlist->length == 0 ? 1 : 0;
}


int seqlist_insert(SeqList* seqlist, size_t pos, SeqListEleType buf) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }

    if (seqlist->length == 0) {
        seqlist->elements[seqlist->length] = buf;
    } else {
        if (pos <= 0 || pos > seqlist->length + 1 || seqlist->length >= seqlist->size) {
            fprintf(stderr, SEQLIST_INSERT_EXCEPTION);
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


int seqlist_remove(SeqList* seqlist, size_t pos, SeqListEleType* buf) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }

    if (seqlist->length == 0 || pos > seqlist->length || pos <= 0) {
        fprintf(stderr, SEQLIST_REMOVE_EXCEPTION);
        return -1;
    }

    *buf = seqlist->elements[pos - 1];

    for (size_t i = pos - 1; i < seqlist->length - 1; i++) {
        seqlist->elements[i] = seqlist->elements[i + 1];
    }

    seqlist->elements[seqlist->length - 1] = INIT_DATA;

    seqlist->length--;
    return 0;
}


int seqlist_search(SeqList* seqlist, size_t* pos, SeqListEleType* buf, int flag) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }

    if (pos == NULL || buf == NULL) {
        fprintf(stderr, SEQLIST_SEARCH_ACCESS_ERROR);
        return -1;
    }

    if (flag == 0) {
        if (seqlist->length == 0 || *pos > seqlist->length || *pos <= 0) {
            fprintf(stderr, SEQLIST_SEARCH_EXCEPTION_INDEX);
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
            fprintf(stderr, SEQLIST_SEARCH_EXCEPTION_NOT_FOUND);
            return -1;
        }
    }
    else {
        fprintf(stderr, SEQLIST_SEARCH_EXCEPTION_INDEX);
        return -1;
    }
    return 0;
}


int seqlist_clean(SeqList** seqlist) {
    if (seqlist == NULL || (*seqlist) == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }
    free((*seqlist)->elements);
    free(*seqlist);
    *seqlist = NULL;
    return 0;
}


int seqlist_display(SeqList* seqlist) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }

    printf("SeqList: {  ");
    for (size_t i = 0; i < seqlist->length; i++) {
        printf("%d  ", seqlist->elements[i]);
    }
    printf("}  length: %zu    size: %zu\n", seqlist->length, seqlist->size);

    return 0;
}
