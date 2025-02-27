#include <stdio.h>
#include <stdlib.h>


typedef int EleType;

#define INIT_DATA 0

typedef struct SeqList {
    EleType* elements;
    size_t length;
    size_t size;
    size_t start;
    size_t end;
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
    seqlist->start = 0;
    seqlist->end = 0;
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
    if (seqlist == NULL) {
            fprintf(stderr, 
                "SeqListInsertionException: Check whether the parameters are valid\n"
            );
            return -1;
    }

    if (pos <= 0 || seqlist->length >= seqlist->size) {
        fprintf(stderr, 
            "SeqListInsertionException: Index access is out of bounds\n"
        );
        return -1;
    }

    if (seqlist->end < seqlist->size) {

        for (int i = seqlist->end; i >= pos; i--) {
            seqlist->elements[i] = seqlist->elements[i - 1];
        }

        seqlist->elements[pos - 1] = ele;

        seqlist->end++;
        seqlist->length++;
    }
    else if (seqlist->end >= seqlist->size && seqlist->start > 0) {
        EleType buf = seqlist->elements[seqlist->start];

        for (int i = seqlist->start; i < pos; i++) {
            seqlist->elements[i - 1] = buf;
            buf = seqlist->elements[i];
        }

        seqlist->elements[pos - 1] = ele;
        seqlist->length++;
        seqlist->start--;
    }

    else {
        fprintf(stderr, 
            "SeqListInsertionException: Index access is out of bounds\n"
        );
        return -1;
    }

    return 0;
}



// TODO: The sequence pointer is abnormal and cannot be executed properly
int seqlist_remove(SeqList* seqlist, size_t pos, EleType* ele) {
    if (seqlist == NULL || pos > seqlist->size 
        || seqlist->length == 0 || pos > seqlist->end) {

            fprintf(stderr, 
                "SeqListRemoveException: Check whether the parameter is valid\n"
            );
            return -1;
    }

    if ((pos - 1) == seqlist->start && seqlist->start > 0) {
        *ele = seqlist->elements[seqlist->start];
        seqlist->elements[seqlist->start] = INIT_DATA;
        seqlist->start++;
    }
    else if ((pos - 1) == seqlist->end && seqlist->end < seqlist->size) {
        *ele = seqlist->elements[seqlist->end];
        seqlist->elements[seqlist->end] = INIT_DATA;
        seqlist->end--;
    }
    else if ((pos - 1) > seqlist->start && (pos - 1) < seqlist->end) {

        EleType buf = seqlist->elements[pos];

        *ele = seqlist->elements[pos - 1];

        for (int i = pos - 1; i < seqlist->end; i++) {
            seqlist->elements[i] = buf;
            buf = seqlist->elements[i + 1];
        }

        seqlist->elements[seqlist->end--] = INIT_DATA;
        seqlist->length--;
    }
    else {
        fprintf(stderr, 
            "SeqListRemoveException: Check whether the parameters are valid\n"
        );
        return -1;
    }

    return 0;

}


int seqlist_display(SeqList* seqlist) {
    if (seqlist == NULL) {
        fprintf(stderr, 
            "SeqListNotFoundError: Check whether parameter `SeqList*` is valid\n"
        );
        return -1;
    }

    printf("SeqList: {  ");
    for (int i = seqlist->start; i < seqlist->end; i++) {
        printf("%d  ", seqlist->elements[i]);
    }
    printf(
        "}  length: %zu    size: %zu    start: %zu    end: %zu\n",
         seqlist->length, seqlist->size, seqlist->start, seqlist->end
    );

    return 0;
}


int main(int argc, char const *argv[])
{
    SeqList* seqlist = seqlist_create(5);
    seqlist_insert(seqlist, 1, 1);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 1, 1);
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 3, 3);
    seqlist_insert(seqlist, 4, 5);
    seqlist_display(seqlist);

    putc('\n', stdout);
    seqlist_insert(seqlist, 3, 6);
    seqlist_display(seqlist);

    if (0) {
        seqlist->length--;
        seqlist->end--;
    }
    if (1) {
        seqlist->length--;
        seqlist->start++;
    }
    seqlist_display(seqlist);

    seqlist_insert(seqlist, 1, 7);
    seqlist_display(seqlist);

    return 0;
}
