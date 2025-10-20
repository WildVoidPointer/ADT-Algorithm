#include<stdio.h>
#include<stdbool.h>


#define MAX_LENGTH 500
#define INIT_DATA 0

typedef char EleType;


typedef struct CircularQueue {
    EleType elements[MAX_LENGTH];
    int front;
    int rear;
} CircularQueue;


void init(CircularQueue *queue) {
    for (int i = 0; i < MAX_LENGTH; i++)
        queue->elements[i] = INIT_DATA;
    
    queue->front = 0;
    queue->rear = 0;
}


bool put(CircularQueue *queue, EleType ele) {
    if ((queue->rear + 1) % MAX_LENGTH == queue->front)
        return false;
    
    queue->elements[queue->rear] = ele;
    queue->rear = (queue->rear + 1) % MAX_LENGTH;
    return true;
}


EleType get(CircularQueue *queue) {
    if (queue->front == queue->rear)
        return INIT_DATA;
    
    EleType _ele = queue->elements[queue->front];
    queue->elements[queue->front] = INIT_DATA;
    queue->front = (queue->front + 1) % MAX_LENGTH;
    return _ele;
}


bool is_empty(CircularQueue queue) {
    return queue.front == queue.rear;
}


int len(CircularQueue *queue) {
    return (queue->rear - queue->front + MAX_LENGTH) % MAX_LENGTH;
}


char get_last_survivor(CircularQueue *queue, int interval) {
    while (len(queue) > 1) {
        for (int i = 0; i < interval - 1 ; i++) 
            put(queue, get(queue));
        get(queue);
    }
    return get(queue);
}


int main(int argc, char const *argv[]) {
    CircularQueue queue;
    init(&queue);
    for (char i = 'a'; i <= 'z'; i++) {
        put(&queue, i);
    }
    int interval = 7;
    char final = get_last_survivor(&queue, interval);
    printf("%c", final);
}
