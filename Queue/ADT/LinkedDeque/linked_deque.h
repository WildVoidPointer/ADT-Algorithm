#ifndef LINKED_DEQUE_H
#define LINKED_DEQUE_H


#include <stdio.h>

#include <stdlib.h>


#ifdef __linux__
    #include <sys/types.h>
#endif


#define LINKED_DEQUE_CREATE_ERROR \
    "LinkedDequeCreateError: Memory initialization of LinkedDeque failed\n"


#define LINKED_DEQUE_CREATE_EXCEPTION \
    "LinkedDequeCreateException: LinkedDeque initialization mode exception\n"


#define LINKED_DEQUE_ACCESS_EXCEPTION \
    "LinkedDequeAccessException: LinkedDeque access address is invalid\n"


#define LINKED_DEQUE_DEQUEUE_EXCEPTION \
    "LinkedDequeDequeueException: LinkedDeque is empty and dequeue operation cannot be performed\n"

typedef int LinkedDequeEleType;


typedef struct LinkedDequeUnit {
    LinkedDequeEleType data;
    struct LinkedDequeUnit* next;
    struct LinkedDequeUnit* prev;
} LinkedDequeUnit;


typedef struct LinkedDeque {
    LinkedDequeUnit* rear;
    LinkedDequeUnit* front;
    size_t length;
    size_t size;
    int is_limited;
} LinkedDeque;


typedef enum LinkedDequeLimitedModeEnum {
    LINKED_DEQUE_LIMITED_MODE = 0,
    LINKED_DEQUE_UNLIMITED_MODE = 1
} LinkedDequeLimitedModeEnum;


LinkedDeque* LinkedDeque_create(
    size_t size, LinkedDequeLimitedModeEnum mode
);

int LinkedDeque_is_empty(LinkedDeque* q);

int LinkedDeque_is_limited(LinkedDeque* q);

ssize_t LinkedDeque_get_size(LinkedDeque* q);

ssize_t LinkedDeque_get_length(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_front(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_rear(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_front_dequeue(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_rear_dequeue(LinkedDeque* q);

int LinkedDeque_front_enqueue(LinkedDeque* q, LinkedDequeEleType data);

int LinkedDeque_rear_enqueue(LinkedDeque* q, LinkedDequeEleType data);

int LinkedDeque_display(LinkedDeque* q);

int LinkedDeque_clean(LinkedDeque** q);

LinkedDequeUnit* LinkedDequeUnit_create(LinkedDequeEleType* data);

int LinkedDequeUnit_clean(LinkedDequeUnit** unit);

#endif
