#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif

#define INIT_DATA 0


typedef int SeqListEleType;


typedef struct SeqList {
    SeqListEleType* elements;
    size_t length;
    size_t size;
} SeqList;


SeqList* seqlist_create(size_t size) {
    SeqList* seqlist = (SeqList*)malloc(sizeof(SeqList));
    if (seqlist == NULL) {
        fprintf(stderr, "SeqListInitError: Failed to allocate memory\n");
        return NULL;
    }
    
    seqlist->elements = (SeqListEleType*)malloc(size * sizeof(SeqListEleType));
    if (seqlist->elements == NULL) {
        fprintf(stderr, "ElementsInitError: Failed to allocate memory\n");
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
            fprintf(stderr, 
                "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"
            );
            return -1;
    }

    if (seqlist->length == 0) {
        seqlist->elements[seqlist->length] = buf;
    } else {
        if (pos <= 0 || pos > seqlist->length + 1 || seqlist->length >= seqlist->size) {
            fprintf(stderr, 
                "SeqListInsertException: Index access is out of bounds\n"
            );
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
            fprintf(stderr, 
                "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"
            );
            return -1;
    }

    if (seqlist->length == 0 || pos > seqlist->length || pos <= 0) {
        fprintf(stderr, 
            "SeqListRemoveException: Index access is out of bounds\n"
        );
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
        fprintf(stderr, 
            "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"
        );
        return -1;
    }

    if (pos == NULL || buf == NULL) {
        fprintf(stderr, 
            "SeqListSearchAccessError: Check whether parameter buffer is valid\n"
        );
        return -1;
    }

    if (flag == 0) {
        if (seqlist->length == 0 || *pos > seqlist->length || *pos <= 0) {
            fprintf(stderr, 
                "SeqListSearchException: Index access is out of bounds\n"
            );
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
            fprintf(stderr, 
                "SeqListSearchException: Specific element not found\n"
            );
            return -1;
        }
    }
    else {
        fprintf(stderr, 
            "SeqListSearchException: Index access is out of bounds\n"
        );
        return -1;
    }
    return 0;
}


int seqlist_clean(SeqList** seqlist) {
    if (seqlist == NULL || (*seqlist) == NULL) {
        fprintf(stderr, 
            "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"
        );
        return -1;
    }
    free((*seqlist)->elements);
    free(*seqlist);
    *seqlist = NULL;
    return 0;
}


int seqlist_display(SeqList* seqlist) {
    if (seqlist == NULL) {
        fprintf(stderr, 
            "SeqListAccessError: Check whether parameter `SeqList*` is valid\n"
        );
        return -1;
    }

    printf("SeqList: {  ");
    for (size_t i = 0; i < seqlist->length; i++) {
        printf("%d  ", seqlist->elements[i]);
    }
    printf(
        "}  length: %zu    size: %zu\n", seqlist->length, seqlist->size
    );

    return 0;
}


int main(int argc, char const *argv[]) {

    SeqList* seqlist = seqlist_create(5);

    seqlist_insert(seqlist, 1, 2);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 1, 1);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 3, 3);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 4, 4);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 5, 5);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 4, 5);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 4, 7);
    seqlist_insert(seqlist, 4, 7);
    seqlist_display(seqlist);

    SeqListEleType delete_buf;
    size_t pos = 0;
    seqlist_remove(seqlist, 5, &delete_buf);
    seqlist_display(seqlist);

    seqlist_remove(seqlist, 1, &delete_buf);
    seqlist_display(seqlist);

    SeqListEleType search_buf = 3;
    size_t search_pos = 1;

    if (0) {
        seqlist_search(seqlist, &search_pos, &search_buf, 0);
        printf("search_pos: %zu    search_buf: %d\n", search_pos, search_buf);  
    } else {
        seqlist_search(seqlist, &search_pos, &search_buf, -1);
        printf("search_pos: %zu    search_buf: %d\n", search_pos, search_buf);
    
    }

    seqlist_clean(&seqlist);
    return 0;
}
