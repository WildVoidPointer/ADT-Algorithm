#include <stdio.h>
#include <stdlib.h>


typedef int EleType;

#define INIT_DATA 0

typedef struct SeqList {
    EleType* elements;
    size_t length;
    size_t size;
    size_t _start;
    size_t _end;
} SeqList;


SeqList* seqlist_create(size_t size) {
    SeqList* seqlist = (SeqList*)malloc(sizeof(SeqList));
    if (seqlist == NULL) {
        fprintf(stderr, "Failed to allocate memory for the SeqList\n");
        return NULL;
    }
    
    seqlist->elements = (EleType*)malloc(size * sizeof(EleType));
    if (seqlist->elements == NULL) {
        fprintf(stderr, "Failed to allocate memory for elements of SeqList\n");
        free(seqlist);
        return NULL;
    }


    seqlist->size = size;
    seqlist->length = 0;
    seqlist->_start = 0;
    seqlist->_end = 0;
    return seqlist;
} 


size_t seqlist_length(SeqList* seqlist) {
    return seqlist->length;
}


int seqlist_is_empty(SeqList* seqlist) {
    return seqlist->length == 0 ? 1 : 0;
}


// TODO: The sequence pointer is abnormal and cannot be executed properly
int seqlist_insert(SeqList* seqlist, size_t pos, EleType ele) {
    if (seqlist == NULL || pos > seqlist->size
        || seqlist->length == seqlist->size) {

            fprintf(stderr, 
                "SeqListInsertionException: Check whether the parameters are valid\n"
            );
            return -1;
    }

    if ((pos - 1) == seqlist->_start && seqlist->_start > 0) {
        seqlist->elements[seqlist->_start] = ele;
        seqlist->_start--;
        seqlist->length++;
    }
    else if ((pos - 1) == seqlist->_end && seqlist->_end < seqlist->size) {
        seqlist->elements[seqlist->_end + 1] = seqlist->elements[seqlist->_end];
        seqlist->elements[seqlist->_end] = ele;
        seqlist->_end++;
        seqlist->length++;
    }
    else if ((pos - 1) > seqlist->_start && (pos - 1) < seqlist->_end) {

        EleType buf = seqlist->elements[pos];

        for (int i = pos; i <= seqlist->_end; i++) {
            seqlist->elements[i] = buf;
            buf = seqlist->elements[i + 1];
        }

        seqlist->elements[seqlist->_end++] = buf;
        seqlist->length++;
    }
    else {
        fprintf(stderr, 
            "SeqListInsertionException: Check whether the parameters are valid\n"
        );
        return -1;
    }

    return 0;
}



// TODO: The sequence pointer is abnormal and cannot be executed properly
int seqlist_remove(SeqList* seqlist, size_t pos, EleType* ele) {
    if (seqlist == NULL || pos > seqlist->size 
        || seqlist->length == 0 || pos > seqlist->_end) {

            fprintf(stderr, 
                "An exception occurs when removing an element from the sequence table.Check whether the parameter is valid\n"
            );
            return -1;
    }

    if ((pos - 1) == seqlist->_start && seqlist->_start > 0) {
        *ele = seqlist->elements[seqlist->_start];
        seqlist->elements[seqlist->_start] = INIT_DATA;
        seqlist->_start++;
    }
    else if ((pos - 1) == seqlist->_end && seqlist->_end < seqlist->size) {
        *ele = seqlist->elements[seqlist->_end];
        seqlist->elements[seqlist->_end] = INIT_DATA;
        seqlist->_end--;
    }
    else if ((pos - 1) > seqlist->_start && (pos - 1) < seqlist->_end) {

        EleType buf = seqlist->elements[pos];

        *ele = seqlist->elements[pos - 1];

        for (int i = pos - 1; i < seqlist->_end; i++) {
            seqlist->elements[i] = buf;
            buf = seqlist->elements[i + 1];
        }

        seqlist->elements[seqlist->_end--] = INIT_DATA;
        seqlist->length--;
    }
    else {
        fprintf(stderr, 
            "The insertion sequence table is abnormal. Check whether the parameters are valid\n"
        );
        return -1;
    }

    return 0;

}


int seqlist_display(SeqList* seqlist) {
    if (seqlist == NULL) {
        fprintf(stderr, 
            "The parameter is abnormal. Check whether parameter `SeqList*` is valid\n"
        );
        return -1;
    }

    printf("SeqList: {  ");
    for (int i = seqlist->_start; i <= seqlist->elements[seqlist->_end]; i++) {
        printf("%d  ", seqlist->elements[i]);
    }
    printf("}  length: %zu    size: %zu\n", seqlist->length, seqlist->size);

    return 0;
}


int main(int argc, char const *argv[])
{
    SeqList* seqlist = seqlist_create(5);
    seqlist_insert(seqlist, 1, 1);
    seqlist_insert(seqlist, 2, 2);
    seqlist_insert(seqlist, 3, 3);
    seqlist_insert(seqlist, 4, 4);
    seqlist_display(seqlist);
    return 0;
}
