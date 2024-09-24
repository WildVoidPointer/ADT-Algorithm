#include<stdio.h>


#define MAX_LENGTH 1000
#define INIT_DATA 0

typedef int EleType;


typedef struct Queue {
    EleType elements[MAX_LENGTH];
    int fornt;
    int rear;
} Queue;


void initialize(Queue *queue) {
    for (int i = 0; i < MAX_LENGTH; i++)
        queue->elements[i] = INIT_DATA;
    
    int front = 0;
    int rear = 0;
}


void put(Queue *queue, EleType ele) {
    if (queue->rear <= MAX_LENGTH) {
        queue->elements[queue->rear] = ele;
        queue->rear++;
    }
}


EleType get(Queue *queue) {
    if (queue->fornt <= queue->rear && queue->rear != 0) {
        EleType _ele = queue->elements[queue->fornt];
        queue->rear++;
        return _ele;
    }
    return INIT_DATA;
}
