#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define INIT_DATA 0

typedef int EleType;

typedef struct Deque {
    EleType* elements;
    size_t size;
    size_t front;
    size_t rear;
    size_t _range;
} Deque;


Deque* deque_create(size_t size) {
    
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    if (deque == NULL) {
        fprintf(stderr, "Failed to allocate memory for the `Deque`\n");
        return NULL;
    }

    deque->elements = (EleType*)malloc((size + 1) * sizeof(EleType));
    if (deque->elements == NULL) {
        fprintf(stderr, "Failed to allocate memory for the `elements` of `Deque`\n");
        free(deque);
        return NULL;
    }

    deque->_range = size + 1;

    for (size_t i = 0; i < deque->_range; i++) {
        deque->elements[i] = INIT_DATA;
    }

    deque->size = size;
    deque->front = 0;
    deque->rear = 0;

    return deque;
}


int deque_is_empty(Deque deque) {
    return deque.front == deque.rear;
}


int deque_is_full(Deque *deque) {
    return (deque->rear + 1) % deque->_range == deque->front;
}


ssize_t deque_length(Deque* deque) {
    return ((deque->rear + deque->_range) - deque->front) % deque->_range;
}


int deque_front_enqueue(Deque* deque, EleType ele) {
    if (deque_is_full(deque)) {
        fprintf(stderr, "Queue is full, enqueue failed\n");
        return -1;
    }

    deque->front = ((deque->front + deque->_range) - 1) % deque->_range;
    deque->elements[deque->front] = ele;
    return 0;
}


int deque_back_enqueue(Deque *deque, EleType ele) {
    if (deque_is_full(deque)) {
        fprintf(stderr, "Queue is full, enqueue failed\n");
        return -1;
    }

    deque->elements[deque->rear] = ele;
    deque->rear = (deque->rear + 1) % deque->_range;
    return 0;
}


int deque_front_dequeue(Deque *deque, EleType* ele) {
    if (deque_is_empty(*deque)) {
        fprintf(stderr, "Queue is empty, queue failed\n");
        return -1;
    }
    
    *ele = deque->elements[deque->front];
    deque->elements[deque->front] = INIT_DATA;
    deque->front = ((deque->front + deque->_range) + 1) % deque->_range;
    return 0;
}


int deque_back_dequeue(Deque *deque, EleType* ele) {
    if (deque_is_empty(*deque)) {
        fprintf(stderr, "Queue is empty, queue failed\n");
        return -1;
    }

    deque->rear = ((deque->rear + deque->_range) - 1) % deque->_range;
    *ele = deque->elements[deque->rear];
    deque->elements[deque->rear] = INIT_DATA;
}


int deque_display(Deque* deque) {
    if (deque == NULL) {
        fprintf(
            stderr, 
            "Parameter is incorrect. Please check whether the `Deque*` type parameter is passed\n"
        );
        return -1;
    }

    size_t start = deque->front;
    size_t end = deque->rear;

    printf("Deque elements: {  ");
    while (start != end) {
        printf("%d  ", deque->elements[start]);
        start = ((start + deque->_range) + 1) % deque->_range;
    }
    printf("}  length: %zu  size: %zu\n", deque_length(deque), deque->size);
    return 0;
}


int deque_clean(Deque** deque) {
    if (*deque == NULL) {
        fprintf(
            stderr, 
            "Parameter is incorrect. Please check whether the `Deque*` type parameter is passed\n"
        );
        return -1;
    }

    free((*deque)->elements);
    free(*deque);
    *deque = NULL;
    return 0;
}


int main(int argc, char const *argv[]) {
    Deque* deque = deque_create(5);

    deque_back_enqueue(deque, 1);
    deque_back_enqueue(deque, 2);
    deque_back_enqueue(deque, 3);
    deque_back_enqueue(deque, 4);
    deque_back_enqueue(deque, 5);

    deque_display(deque);

    EleType res;

    deque_back_dequeue(deque, &res);
    deque_display(deque);

    deque_front_dequeue(deque, &res);
    deque_display(deque);

    deque_back_enqueue(deque, 6);
    deque_display(deque);

    deque_front_enqueue(deque, 6);
    deque_display(deque);

    deque_front_dequeue(deque, &res);
    deque_front_dequeue(deque, &res);
    deque_front_dequeue(deque, &res);
    deque_front_dequeue(deque, &res);
    deque_front_dequeue(deque, &res);

    deque_display(deque);

    deque_clean(&deque);
    
    return 0;
}
