#ifndef CIRCULAR_DEQUE_H
#define CIRCULAR_DEQUE_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define CIRCULAR_DEQUE_INIT_ERROR \
    "CircularDequeInitError: Failed to allocate memory for the `CircularDeque`\n"

#define CIRCULAR_DEQUE_ELEMENTS_INIT_ERROR \
    "CircularDequeElementsInitError: Failed to allocate memory for the `elements` of `CircularDeque`\n"

#define CIRCULAR_DEQUE_ACCESS_ERROR \
    "CircularDequeAccessException: Please check whether the `CircularDeque*` type parameter is passed\n"

#define CIRCULAR_DEQUE_ENQUEUE_ERROR "CircularDequeEnqueueException: Queue is full, enqueue failed\n"

#define CIRCULAR_DEQUE_DEQUEUE_ERROR "CircularDequeDequeueException: Queue is empty, dequeue failed\n"


typedef enum CircularDequeInitModeEnum {
    CIRCULAR_DEQUE_INIT_DISABLE,
    CIRCULAR_DEQUE_INIT_ENABLE
} CircularDequeInitModeEnum;

typedef int CircularDequeEleType;


typedef struct CircularDeque {
    CircularDequeEleType* elements;
    CircularDequeEleType init;
    int is_init;
    size_t size;
    size_t front;
    size_t rear;
    size_t _range;
} CircularDeque;


CircularDeque* 
CircularDeque_create(size_t size, CircularDequeInitModeEnum is_init, CircularDequeEleType* init);

int CircularDeque_front_enqueue(CircularDeque* deque, CircularDequeEleType ele);

int CircularDeque_back_enqueue(CircularDeque *deque, CircularDequeEleType ele);

int CircularDeque_front_dequeue(CircularDeque *deque, CircularDequeEleType* ele);

int CircularDeque_back_dequeue(CircularDeque *deque, CircularDequeEleType* ele);

int CircularDeque_display(CircularDeque* deque);

int CircularDeque_clean(CircularDeque** deque);


int CircularDeque_is_empty(CircularDeque* deque);

int CircularDeque_is_full(CircularDeque *deque);

ssize_t CircularDeque_length(CircularDeque* deque);


#endif // CIRCULAR_DEQUE_H