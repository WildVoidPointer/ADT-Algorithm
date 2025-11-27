#ifndef LINKED_DEQUE_H_
#define LINKED_DEQUE_H_


#include <stdio.h>

#include <stdlib.h>


#ifdef __linux__
    #include <sys/types.h>
#endif


#define LINKED_DEQUE_CREATE_ERROR \
    "LinkedDequeCreateError: " \
    "Memory initialization of LinkedDeque failed\n"


#define LINKED_DEQUE_BUILD_EXCEPTION \
    "LinkedDequeBuildException: " \
    "The initialization data for " \
    "LinkedDeque build cannot be accessed or is invalid\n"


#define LINKED_DEQUE_BUILD_ERROR \
    "LinkedDequeBuildError: " \
    "Memory initialization of LinkedDeque failed in build\n"


#define LINKED_DEQUE_CREATE_EXCEPTION \
    "LinkedDequeCreateException: " \
    "LinkedDeque initialization mode exception\n"


#define LINKED_DEQUE_ACCESS_EXCEPTION \
    "LinkedDequeAccessException: LinkedDeque access address is invalid\n"


#define LINKED_DEQUE_DEQUEUE_EXCEPTION \
    "LinkedDequeDequeueException: " \
    "LinkedDeque is empty and dequeue operation cannot be performed\n"


#define LINKED_DEQUE_ENQUEUE_EXCEPTION \
    "LinkedDequeEnqueueException: " \
    "LinkedDeque is filled and enqueue operation cannot be performed\n"


#define LINKED_DEQUE_ENQUEUE_FAILED_ERROR \
    "LinkedDequeEnqueueFaildError: " \
    "Memory initialization of new LinkedDequeUnit failed\n"


#define LINKED_DEQUE_UNIT_CREATE_ERROR \
    "LinkedDequeUnitCreateError: " \
    "Memory initialization of LinkedDequeUnit failed\n"


#define LINKED_DEQUE_UNIT_BUFFER_CREATE_ERROR \
    "LinkedDequeUnitBufferCreateError: " \
    "Memory initialization of LinkedDequeUnitBuffer failed\n"


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
} LinkedDeque;


LinkedDeque* LinkedDeque_create(size_t size);

LinkedDeque* LinkedDeque_build_of_array(
    size_t len, LinkedDequeEleType* arr
);

int LinkedDeque_is_empty(LinkedDeque* q);

int LinkedDeque_is_filled(LinkedDeque* q);

ssize_t LinkedDeque_get_size(LinkedDeque* q);

ssize_t LinkedDeque_get_length(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_front(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_rear(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_front_dequeue(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_rear_dequeue(LinkedDeque* q);

int LinkedDeque_front_enqueue(
    LinkedDeque* q, LinkedDequeEleType data
);

int LinkedDeque_rear_enqueue(
    LinkedDeque* q, LinkedDequeEleType data
);

int LinkedDeque_display(LinkedDeque* q);

int LinkedDeque_destroy(LinkedDeque** q);

LinkedDequeUnit* LinkedDequeUnit_create(LinkedDequeEleType* data);

int LinkedDequeUnit_destroy(LinkedDequeUnit** unit);

#endif
