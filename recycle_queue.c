#include<stdio.h>
#include<stdbool.h>


#define MAX_LENGTH 2
#define INIT_DATA 0

typedef int EleType;


typedef struct Queue {
    EleType elements[MAX_LENGTH];
    int front;
    int rear;
} Queue;


void initialize(Queue *queue) {
    for (int i = 0; i < MAX_LENGTH; i++)
        queue->elements[i] = INIT_DATA;
    
    queue->front = 0;
    queue->rear = 0;
}


bool put(Queue *queue, EleType ele) {
    if ((queue->rear + 1) % MAX_LENGTH == queue->front)
        return false;
    
    queue->elements[queue->rear] = ele;
    queue->rear = (queue->rear + 1) % MAX_LENGTH;
    return true;
}


EleType get(Queue *queue) {
    if (queue->front == queue->rear)
        return INIT_DATA;
    
    EleType _ele = queue->elements[queue->front];
    queue->elements[queue->front] = INIT_DATA;
    queue->front = (queue->front + 1) % MAX_LENGTH;
    return _ele;
}


bool is_empty(Queue queue) {
    return queue.front == queue.rear;
}


int len(Queue queue) {
    return (queue.rear - queue.front + MAX_LENGTH) % MAX_LENGTH;
}


int main(int argc, char const *argv[]) {
    Queue queue;
    initialize(&queue);
    put(&queue, 21);
    put(&queue, 22);
    put(&queue, 23);
    int current_len = len(queue);
    for (int i = queue.front; i < queue.rear; i++)
        printf("%d  ", queue.elements[i]);
    puts("");
    printf("current_len: %d\n", current_len);
    
    EleType current_element =  get(&queue);
    for (int i = queue.front; i < queue.rear; i++)
        printf("%d  ", queue.elements[i]);
    puts("");
    
    current_len = len(queue);
    printf("current_len: %d\n", current_len);
    
    printf("current_element: %d\n", current_element);
    return 0;
}
