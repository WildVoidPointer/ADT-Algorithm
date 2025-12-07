#include "array_deque.h"


ArrayDeque* ArrayDeque_create(size_t size) {

    ArrayDeque* deque = (ArrayDeque*)malloc(sizeof(ArrayDeque));
    if (deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_INIT_ERROR);
        return NULL;
    }

    deque->elements = (ArrayDequeDataType*) malloc (
        (size + 1) * sizeof(ArrayDequeDataType)
    );
    if (deque->elements == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ELEMENTS_INIT_ERROR);
        free(deque);
        return NULL;
    }

    deque->size = size;
    deque->front = 0;
    deque->rear = 0;

    return deque;
}


int ArrayDeque_is_empty(ArrayDeque* deque) {
    return deque != NULL ? 
        deque->front == deque->rear 
        : -1;
}


int ArrayDeque_is_full(ArrayDeque *deque) {
    return deque != NULL ? 
        (deque->rear + 1) % deque->_range == deque->front
        : -1;
}


ssize_t ArrayDeque_length(ArrayDeque* deque) {
    return ((deque->rear + deque->_range) - deque->front) % deque->_range;
}


int ArrayDeque_front_enqueue(
    ArrayDeque* deque, ArrayDequeDataType ele
) {
    if (deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }
    
    if (ArrayDeque_is_full(deque)) {
        fprintf(stderr, ARRAY_DEQUE_ENQUEUE_ERROR);
        return -1;
    }

    deque->front = ((deque->front + deque->_range) - 1) % deque->_range;
    deque->elements[deque->front] = ele;
    return 0;
}


int ArrayDeque_back_enqueue(
    ArrayDeque *deque, ArrayDequeDataType ele
) {
    if (deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    if (ArrayDeque_is_full(deque)) {
        fprintf(stderr, ARRAY_DEQUE_ENQUEUE_ERROR);
        return -1;
    }

    deque->elements[deque->rear] = ele;
    deque->rear = (deque->rear + 1) % deque->_range;
    return 0;
}


int ArrayDeque_front_dequeue(
    ArrayDeque *deque, ArrayDequeDataType* ele
) {
    if (deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    if (ArrayDeque_is_empty(deque)) {
        fprintf(stderr, ARRAY_DEQUE_DEQUEUE_ERROR);
        return -1;
    }
    
    *ele = deque->elements[deque->front];
    deque->front = ((deque->front + deque->_range) + 1) % deque->_range;
    return 0;
}


int ArrayDeque_back_dequeue(
    ArrayDeque *deque, ArrayDequeDataType* ele
) {

    if (deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    if (ArrayDeque_is_empty(deque)) {
        fprintf(stderr, ARRAY_DEQUE_DEQUEUE_ERROR);
        return -1;
    }

    deque->rear = ((deque->rear + deque->_range) - 1) % deque->_range;
    *ele = deque->elements[deque->rear];
    return 0;
}


int ArrayDeque_display(ArrayDeque* deque) {
    if (deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    size_t start = deque->front;
    size_t end = deque->rear;

    printf("ArrayDeque elements: {  ");

    while (start != end) {
        printf("%d  ", deque->elements[start]);
        start = ((start + deque->_range) + 1) % deque->_range;
    }

    printf(
        "}  length: %zu  size: %zu\n", 
        ArrayDeque_length(deque), 
        deque->size
    );

    return 0;
}


int ArrayDeque_destroy(ArrayDeque** deque) {
    if (deque == NULL || *deque == NULL) {
        fprintf(stderr, ARRAY_DEQUE_ACCESS_EXCEPTION);
        return -1;
    }

    free((*deque)->elements);
    free(*deque);
    *deque = NULL;
    return 0;
}
