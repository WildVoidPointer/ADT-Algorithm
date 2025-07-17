#include "circular_deque.h"


CircularDeque* 
CircularDeque_create(size_t size, CircularDequeInitModeEnum is_init, CircularDequeEleType* init) {
    CircularDeque* deque = (CircularDeque*)malloc(sizeof(CircularDeque));
    if (deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_INIT_ERROR);
        return NULL;
    }

    deque->elements = (CircularDequeEleType*)malloc((size + 1) * sizeof(CircularDequeEleType));
    if (deque->elements == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ELEMENTS_INIT_ERROR);
        free(deque);
        return NULL;
    }

    deque->_range = size + 1;
    if (is_init == (CircularDequeInitModeEnum)CIRCULAR_DEQUE_INIT_ENABLE) {
        deque->init = *init;
        deque->is_init = 1;

        for (size_t i = 0; i < deque->_range; i++) {
            deque->elements[i] = *init;
        }
    }

    deque->is_init = 0;
    deque->size = size;
    deque->front = 0;
    deque->rear = 0;

    return deque;
}


int CircularDeque_is_empty(CircularDeque* deque) {
    return deque != NULL ? deque->front == deque->rear : -1;
}


int CircularDeque_is_full(CircularDeque *deque) {
    return deque != NULL ? (deque->rear + 1) % deque->_range == deque->front: -1;
}


ssize_t CircularDeque_length(CircularDeque* deque) {
    return ((deque->rear + deque->_range) - deque->front) % deque->_range;
}


int CircularDeque_front_enqueue(CircularDeque* deque, CircularDequeEleType ele) {
    if (deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ACCESS_ERROR);
        return -1;
    }
    
    if (CircularDeque_is_full(deque)) {
        fprintf(stderr, CIRCULAR_DEQUE_ENQUEUE_ERROR);
        return -1;
    }

    deque->front = ((deque->front + deque->_range) - 1) % deque->_range;
    deque->elements[deque->front] = ele;
    return 0;
}


int CircularDeque_back_enqueue(CircularDeque *deque, CircularDequeEleType ele) {
    if (deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ACCESS_ERROR);
        return -1;
    }

    if (CircularDeque_is_full(deque)) {
        fprintf(stderr, CIRCULAR_DEQUE_ENQUEUE_ERROR);
        return -1;
    }

    deque->elements[deque->rear] = ele;
    deque->rear = (deque->rear + 1) % deque->_range;
    return 0;
}


int CircularDeque_front_dequeue(CircularDeque *deque, CircularDequeEleType* ele) {
    if (deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ACCESS_ERROR);
        return -1;
    }

    if (CircularDeque_is_empty(deque)) {
        fprintf(stderr, CIRCULAR_DEQUE_DEQUEUE_ERROR);
        return -1;
    }
    
    *ele = deque->elements[deque->front];
    if (deque->is_init) {
        deque->elements[deque->front] = deque->init;
    }
    deque->front = ((deque->front + deque->_range) + 1) % deque->_range;
    return 0;
}


int CircularDeque_back_dequeue(CircularDeque *deque, CircularDequeEleType* ele) {
    if (deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ACCESS_ERROR);
        return -1;
    }

    if (CircularDeque_is_empty(deque)) {
        fprintf(stderr, CIRCULAR_DEQUE_DEQUEUE_ERROR);
        return -1;
    }

    deque->rear = ((deque->rear + deque->_range) - 1) % deque->_range;
    *ele = deque->elements[deque->rear];
    if (deque->is_init) {
        deque->elements[deque->rear] = deque->init;
    }
    return 0;
}


int CircularDeque_display(CircularDeque* deque) {
    if (deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ACCESS_ERROR);
        return -1;
    }

    size_t start = deque->front;
    size_t end = deque->rear;

    printf("CircularDeque elements: {  ");
    while (start != end) {
        printf("%d  ", deque->elements[start]);
        start = ((start + deque->_range) + 1) % deque->_range;
    }
    printf("}  length: %zu  size: %zu\n", CircularDeque_length(deque), deque->size);
    return 0;
}


int CircularDeque_clean(CircularDeque** deque) {
    if (deque == NULL || *deque == NULL) {
        fprintf(stderr, CIRCULAR_DEQUE_ACCESS_ERROR);
        return -1;
    }

    free((*deque)->elements);
    free(*deque);
    *deque = NULL;
    return 0;
}
