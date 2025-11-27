#ifndef ARRAY_DEQUE_H_
#define ARRAY_DEQUE_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define ARRAY_DEQUE_INIT_ERROR \
    "ArrayDequeInitError: " \
    "Failed to allocate memory for the `ArrayDeque`\n"


#define ARRAY_DEQUE_ELEMENTS_INIT_ERROR \
    "ArrayDequeElementsInitError: " \
    "Failed to allocate memory for the `elements` of `ArrayDeque`\n"


#define ARRAY_DEQUE_ACCESS_ERROR \
    "ArrayDequeAccessException: " \
    "Please check whether the `ArrayDeque*` type parameter is passed\n"


#define ARRAY_DEQUE_ENQUEUE_ERROR \
    "ArrayDequeEnqueueException: Queue is full, enqueue failed\n"


#define ARRAY_DEQUE_DEQUEUE_ERROR \
    "ArrayDequeDequeueException: Queue is empty, dequeue failed\n"


typedef int ArrayDequeDataType;


typedef struct ArrayDeque {
    ArrayDequeDataType* elements;
    size_t size;
    size_t front;
    size_t rear;
    size_t _range;
} ArrayDeque;


ArrayDeque* ArrayDeque_create(size_t size);

int ArrayDeque_front_enqueue(
    ArrayDeque* deque, ArrayDequeDataType ele
);

int ArrayDeque_back_enqueue(
    ArrayDeque *deque, ArrayDequeDataType ele
);

int ArrayDeque_front_dequeue(
    ArrayDeque *deque, ArrayDequeDataType* ele
);

int ArrayDeque_back_dequeue(
    ArrayDeque *deque, ArrayDequeDataType* ele
);

int ArrayDeque_display(ArrayDeque* deque);

int ArrayDeque_destroy(ArrayDeque** deque);

int ArrayDeque_is_empty(ArrayDeque* deque);

int ArrayDeque_is_full(ArrayDeque *deque);

ssize_t ArrayDeque_length(ArrayDeque* deque);


#endif // ARRAY_DEQUE_H