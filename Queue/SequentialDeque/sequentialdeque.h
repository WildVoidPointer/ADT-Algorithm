#ifndef SEQUENTIAL_DEQUE_H
#define SEQUENTIAL_DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define SEQUENTIAL_DEQUE_INIT_ERROR \
    "SequentialDequeInitError: Failed to allocate memory for the `SequentialDeque`\n"

#define SEQUENTIAL_DEQUE_ELEMENTS_INIT_ERROR \
    "SequentialDequeElementsInitError: Failed to allocate memory for the `elements` of `SequentialDeque`\n"

#define SEQUENTIAL_DEQUE_ACCESS_ERROR \
    "SequentialDequeAccessException: Please check whether the `SequentialDeque*` type parameter is passed\n"

#define SEQUENTIAL_DEQUE_ENQUEUE_ERROR "SequentialDequeEnqueueException: Queue is full, enqueue failed\n"

#define SEQUENTIAL_DEQUE_DEQUEUE_ERROR "SequentialDequeDequeueException: Queue is empty, dequeue failed\n"

#define DEQUE_INIT_ENABLE 1
#define DEQUE_INIT_DISABLE 0


typedef int SequentialDequeEleType;


typedef struct SequentialDeque {
    SequentialDequeEleType* elements;
    SequentialDequeEleType init;
    int is_init;
    size_t size;
    size_t front;
    size_t rear;
    size_t _range;
} SequentialDeque;


SequentialDeque* deque_create(size_t size, int is_init, SequentialDequeEleType* init);

int deque_front_enqueue(SequentialDeque* deque, SequentialDequeEleType ele);

int deque_back_enqueue(SequentialDeque *deque, SequentialDequeEleType ele);

int deque_front_dequeue(SequentialDeque *deque, SequentialDequeEleType* ele);

int deque_back_dequeue(SequentialDeque *deque, SequentialDequeEleType* ele);

int deque_display(SequentialDeque* deque);

int deque_clean(SequentialDeque** deque);


int deque_is_empty(SequentialDeque* deque);

int deque_is_full(SequentialDeque *deque);

ssize_t deque_length(SequentialDeque* deque);


#endif // SEQUENTIAL_DEQUE_H