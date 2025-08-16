#include "linked_deque.h"
#include <stdio.h>


LinkedDeque* LinkedDeque_create(size_t size, LinkedDequeLimitedModeEnum mode) {
    LinkedDeque* q = (LinkedDeque*) malloc (sizeof(LinkedDeque));
    if (q == NULL) {
        fprintf(stderr, LINKED_DEQUE_CREATE_ERROR);
        return NULL;
    }

    if (mode == LINKED_DEQUE_LIMITED_MODE) {
        q->is_limited = 1;
        q->size = size;
    } else if (mode == LINKED_DEQUE_UNLIMITED_MODE) {
        q->is_limited = 0;
    } else {
        fprintf(stderr, LINKED_DEQUE_CREATE_EXCEPTION);
        LinkedDeque_clean(&q);
        return NULL;
    }

    q->front = q->rear = NULL;
    q->length = 0;
    return q;
}


int LinkedDeque_is_empty(LinkedDeque* q);

ssize_t LinkedDeque_get_size(LinkedDeque* q);

ssize_t LinkedDeque_get_length(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_front(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_rear(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_front_dequeue(LinkedDeque* q);

LinkedDequeUnit* LinkedDeque_rear_dequeue(LinkedDeque* q);

int LinkedDeque_front_enqueue(LinkedDeque* q, LinkedDequeEleType data);

int LinkedDeque_rear_enqueue(LinkedDeque* q, LinkedDequeEleType data);

int LinkedDeque_display(LinkedDeque* q);


int LinkedDeque_clean(LinkedDeque** q) {
    if (q == NULL || *q == NULL) {
        fprintf(stderr, LINKED_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    
}


LinkedDequeUnit* LinkedDequeUnit_create(LinkedDequeEleType* data);

int LinkedDequeUnit_clean(LinkedDequeUnit** unit);
