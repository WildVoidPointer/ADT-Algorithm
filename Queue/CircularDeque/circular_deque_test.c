#include "circular_deque.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    CircularDeque* deque = circular_deque_create(5, CIRCULAR_DEQUE_INIT_DISABLE, NULL);

    circular_deque_back_enqueue(deque, 1);
    circular_deque_back_enqueue(deque, 2);
    circular_deque_back_enqueue(deque, 3);
    circular_deque_back_enqueue(deque, 4);
    circular_deque_back_enqueue(deque, 5);
    circular_deque_display(deque);

    circular_deque_back_enqueue(deque, 6);
    circular_deque_display(deque);

    CircularDequeEleType res;

    circular_deque_back_dequeue(deque, &res);
    circular_deque_display(deque);

    circular_deque_back_dequeue(deque, &res);
    circular_deque_back_dequeue(deque, &res);
    circular_deque_back_dequeue(deque, &res);
    circular_deque_back_dequeue(deque, &res);
    circular_deque_display(deque);

    circular_deque_front_dequeue(deque, &res);
    circular_deque_display(deque);

    circular_deque_back_enqueue(deque, 6);
    circular_deque_display(deque);

    circular_deque_front_enqueue(deque, 6);
    circular_deque_display(deque);

    circular_deque_clean(&deque);
    circular_deque_display(deque);
    
    return 0;
}