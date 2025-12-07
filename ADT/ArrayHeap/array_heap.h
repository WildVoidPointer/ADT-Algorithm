#ifndef ARRAY_HEAP_H_
#define ARRAY_HEAP_H_



#include <stdio.h>
#include <stdlib.h>


#define ARRAY_HEAP_CREATE_ERROR \
    "ArrayHeapInitError: " \
    "Failed to allocate memory for the `ArrayHeap`\n"


#define ARRAY_HEAP_ACCESS_EXCEPTION \
    "ArrayHeapAccessException: " \
    "Check whether parameter `ArrayHeap*` is valid ?\n"


typedef int ArrayHeapDataType;


typedef struct ArrayHeap {
    ArrayHeapDataType* data;
    int size;
    int length;
} ArrayHeap;


ArrayHeap* ArrayHeap_create(int size);


int ArrayHeap_destroy(ArrayHeap** heap);



#endif
