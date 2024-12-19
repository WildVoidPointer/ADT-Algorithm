#include <stdio.h>
#include <stdbool.h>

#define MAX_LENGTH 500
#define INIT_DATA 0

typedef int EleType;

typedef struct Deque {
    EleType elements[MAX_LENGTH];
    int front;
    int rear;
} Deque;


void init(Deque *deque) {
    for (int i = 0; i < MAX_LENGTH; i++)
        deque->elements[i] = INIT_DATA;
    
    deque->front = 0;
    deque->rear = 0;
}

bool is_empty(Deque deque) {
    return deque.front == deque.rear;
}

bool is_full(Deque *deque) {
    return (deque->rear + 1) % MAX_LENGTH == deque->front;
}


int len(Deque deque) {
    return (deque.rear - deque.front + MAX_LENGTH) % MAX_LENGTH;
}


bool push_back(Deque *deque, EleType ele) {
    if (is_full(deque))
        return false;
    
    deque->elements[deque->rear] = ele;
    deque->rear = (deque->rear + 1) % MAX_LENGTH;
    return true;
}

bool push_front(Deque *deque, EleType ele) {
    if (is_full(deque))
        return false;
    
    deque->front = (deque->front - 1 + MAX_LENGTH) % MAX_LENGTH;
    deque->elements[deque->front] = ele;
    return true;
}


EleType pop_front(Deque *deque) {
    if (is_empty(*deque))
        return INIT_DATA;
    
    EleType _ele = deque->elements[deque->front];
    deque->elements[deque->front] = INIT_DATA;
    deque->front = (deque->front + 1) % MAX_LENGTH;
    return _ele;
}


EleType pop_back(Deque *deque) {
    if (is_empty(*deque))
        return INIT_DATA;
    
    deque->rear = (deque->rear - 1 + MAX_LENGTH) % MAX_LENGTH;
    EleType _ele = deque->elements[deque->rear];
    deque->elements[deque->rear] = INIT_DATA;
    return _ele;
}


int main(int argc, char const *argv[]) {
    Deque deque;
    init(&deque);
    return 0;
}
