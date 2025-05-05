#include "sequentialdeque.h"

SequentialDeque* deque_create(size_t size, int is_init, SequentialDequeEleType* init) {
    SequentialDeque* deque = (SequentialDeque*)malloc(sizeof(SequentialDeque));
    if (deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_INIT_ERROR);
        return NULL;
    }

    deque->elements = (SequentialDequeEleType*)malloc((size + 1) * sizeof(SequentialDequeEleType));
    if (deque->elements == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ELEMENTS_INIT_ERROR);
        free(deque);
        return NULL;
    }

    deque->_range = size + 1;
    if (is_init) {
        deque->init = *init;
        deque->is_init = is_init;

        for (size_t i = 0; i < deque->_range; i++) {
            deque->elements[i] = *init;
        }
    }

    deque->size = size;
    deque->front = 0;
    deque->rear = 0;

    return deque;
}


int deque_is_empty(SequentialDeque* deque) {
    return deque != NULL ? deque->front == deque->rear : -1;
}


int deque_is_full(SequentialDeque *deque) {
    return deque != NULL ? (deque->rear + 1) % deque->_range == deque->front: -1;
}


ssize_t deque_length(SequentialDeque* deque) {
    return ((deque->rear + deque->_range) - deque->front) % deque->_range;
}


int deque_front_enqueue(SequentialDeque* deque, SequentialDequeEleType ele) {
    if (deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ACCESS_ERROR);
        return -1;
    }
    
    if (deque_is_full(deque)) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ENQUEUE_ERROR);
        return -1;
    }

    deque->front = ((deque->front + deque->_range) - 1) % deque->_range;
    deque->elements[deque->front] = ele;
    return 0;
}


int deque_back_enqueue(SequentialDeque *deque, SequentialDequeEleType ele) {
    if (deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ACCESS_ERROR);
        return -1;
    }

    if (deque_is_full(deque)) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ENQUEUE_ERROR);
        return -1;
    }

    deque->elements[deque->rear] = ele;
    deque->rear = (deque->rear + 1) % deque->_range;
    return 0;
}


int deque_front_dequeue(SequentialDeque *deque, SequentialDequeEleType* ele) {
    if (deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ACCESS_ERROR);
        return -1;
    }

    if (deque_is_empty(deque)) {
        fprintf(stderr, SEQUENTIAL_DEQUE_DEQUEUE_ERROR);
        return -1;
    }
    
    *ele = deque->elements[deque->front];
    if (deque->is_init) {
        deque->elements[deque->front] = deque->init;
    }
    deque->front = ((deque->front + deque->_range) + 1) % deque->_range;
    return 0;
}


int deque_back_dequeue(SequentialDeque *deque, SequentialDequeEleType* ele) {
    if (deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ACCESS_ERROR);
        return -1;
    }

    if (deque_is_empty(deque)) {
        fprintf(stderr, SEQUENTIAL_DEQUE_DEQUEUE_ERROR);
        return -1;
    }

    deque->rear = ((deque->rear + deque->_range) - 1) % deque->_range;
    *ele = deque->elements[deque->rear];
    if (deque->is_init) {
        deque->elements[deque->rear] = deque->init;
    }
    return 0;
}


int deque_display(SequentialDeque* deque) {
    if (deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ACCESS_ERROR);
        return -1;
    }

    size_t start = deque->front;
    size_t end = deque->rear;

    printf("SequentialDeque elements: {  ");
    while (start != end) {
        printf("%d  ", deque->elements[start]);
        start = ((start + deque->_range) + 1) % deque->_range;
    }
    printf("}  length: %zu  size: %zu\n", deque_length(deque), deque->size);
    return 0;
}


int deque_clean(SequentialDeque** deque) {
    if (*deque == NULL) {
        fprintf(stderr, SEQUENTIAL_DEQUE_ACCESS_ERROR);
        return -1;
    }

    free((*deque)->elements);
    free(*deque);
    *deque = NULL;
    return 0;
}