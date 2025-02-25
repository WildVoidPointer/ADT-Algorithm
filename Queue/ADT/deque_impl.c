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
} Deque;


Deque* deque_create(size_t max_size) {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    if (deque == NULL) {
        fprintf(stderr, "Failed to allocate memory for the `Deque`\n");
        return NULL;
    }

    deque->elements = (EleType*)malloc(max_size * sizeof(EleType));
    if (deque->elements == NULL) {
        fprintf(stderr, "Failed to allocate memory for the `elements` of `Deque`\n");
        free(deque);
        return NULL;
    }

    for (size_t i = 0; i < max_size; i++) {
        deque->elements[i] = INIT_DATA;
    }

    deque->size = max_size;
    deque->front = 0;
    deque->rear = 0;

    return deque;
}


int deque_is_empty(Deque deque) {
    return deque.front == deque.rear;
}


int deque_is_full(Deque *deque) {
    return (deque->rear + 1) % deque->size == deque->front;
}


ssize_t deque_length(Deque deque) {
    return ((deque.rear + deque.size) - deque.front) % deque.size;
}


int deque_enqueue(Deque *deque, EleType ele) {
    if (deque_is_full(deque)) {
        fprintf(stderr, "Queue is full, enqueue failed\n");
        return -1;
    }

    deque->elements[deque->rear] = ele;
    deque->rear = (deque->rear + 1) % deque->size;
    return 0;
}


int deque_dequeue(Deque *deque, EleType ele) {
    if (deque_is_empty(*deque)) {
        fprintf(stderr, "Queue is empty, queue failed\n");
        return -1;
    }
    
    deque->front = (deque->front - 1 + deque->size) % deque->size;
    deque->elements[deque->front] = ele;
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
    Deque* deque = deque_create(23);

    printf("%p\n", deque);

    deque_clean(&deque);

    printf("%p\n", deque);
    
    return 0;
}
