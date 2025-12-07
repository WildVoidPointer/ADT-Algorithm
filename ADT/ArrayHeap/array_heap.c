#include "array_heap.h"


ArrayHeap* ArrayHeap_create(int size) {
    ArrayHeap* heap = (ArrayHeap*) malloc (sizeof(ArrayHeap));
    if (heap == NULL) {
        fprintf(stderr, ARRAY_HEAP_CREATE_ERROR);
        return NULL;
    }

    heap->data = (ArrayHeapDataType*) malloc (sizeof(ArrayHeapDataType) * size);
    if (heap->data == NULL) {
        fprintf(stderr, ARRAY_HEAP_CREATE_ERROR);
        free(heap);
    }

    heap->size = size;
    heap->length = 0;
    return heap;
}


int ArrayHeap_destroy(ArrayHeap** heap) {
    if (heap == NULL || *heap == NULL) {
        fprintf(stderr, ARRAY_HEAP_ACCESS_EXCEPTION);
        return -1;
    }

    free((*heap)->data);
    free(*heap);
    *heap = NULL;
    return 0;
}

