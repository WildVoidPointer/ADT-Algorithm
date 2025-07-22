#include "seqlist.h"


SeqList* 
SeqList_create(size_t size, SeqListInitModeEnum is_init, SeqListEleType *init_data) {

    SeqList* seqlist = (SeqList*)malloc(sizeof(SeqList));
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_CREATE_ERROR);
        return NULL;
    }

    seqlist->elements = (SeqListEleType*)malloc(size * sizeof(SeqListEleType));
    if (seqlist->elements == NULL) {
        fprintf(stderr, ELEMENTS_INIT_ERROR);
        free(seqlist);
        return NULL;
    }

    if (is_init == (SeqListInitModeEnum)SEQLIST_INIT_ENABLE) {
        seqlist->is_init = 1;
        seqlist->init_data = *init_data;
        for (size_t i = 0; i < size; i++) {
            seqlist->elements[i] = *init_data;
        }
    } else {
        seqlist->is_init = 0;
    }

    
    seqlist->size = size;
    seqlist->length = 0;
    return seqlist;
}


int 
SeqList_expand(SeqList* seqlist, size_t expand_size, SeqListInitModeEnum is_init) {
    if (seqlist == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }

    SeqListEleType* tmp = (SeqListEleType*) 
        realloc (seqlist->elements, sizeof(SeqListEleType) * (seqlist->size + expand_size));

    if (tmp == NULL) {
        fprintf(stderr, SEQLIST_EXPAND_ERROR);
        return -1;
    } else {
        seqlist->elements = tmp;
    }

    if (is_init == (SeqListInitModeEnum) SEQLIST_INIT_ENABLE || seqlist->is_init) {
        for (size_t i = seqlist->size; i < (seqlist->size + expand_size); i++) {
            seqlist->elements[i] = seqlist->init_data;
        }
    }
    seqlist->size = seqlist->size + expand_size;
    return 0;
}


size_t SeqList_length(SeqList* seqlist) {
    return seqlist->length;
}


int SeqList_is_empty(SeqList* seqlist) {
    return seqlist->length == 0 ? 1 : 0;
}


int SeqList_insert(SeqList* seqlist, size_t pos, SeqListEleType buf) {
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


int SeqList_remove(SeqList* seqlist, size_t pos, SeqListEleType* buf) {
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

    if (seqlist->is_init) {
        seqlist->elements[seqlist->length - 1] = seqlist->init_data;
    }

    seqlist->length--;
    return 0;
}


int SeqList_search(SeqList* seqlist, size_t* pos, SeqListEleType* buf, int flag) {
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
            fprintf(stderr, SEQLIST_SEARCH_NOT_FOUND);
            return -1;
        }
    }
    else {
        fprintf(stderr, SEQLIST_SEARCH_EXCEPTION_INDEX);
        return -1;
    }
    return 0;
}


int SeqList_clean(SeqList** seqlist) {
    if (seqlist == NULL || (*seqlist) == NULL) {
        fprintf(stderr, SEQLIST_ACCESS_ERROR);
        return -1;
    }
    free((*seqlist)->elements);
    free(*seqlist);
    *seqlist = NULL;
    return 0;
}


int SeqList_display(SeqList* seqlist) {
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
