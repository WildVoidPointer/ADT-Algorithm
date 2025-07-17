#include "circular_deque.h"
#include <stdio.h>


int main(int argc, char const *argv[]) {
    CircularDeque* deque = CircularDeque_create(5, CIRCULAR_DEQUE_INIT_DISABLE, NULL);

    CircularDeque_back_enqueue(deque, 1);
    CircularDeque_back_enqueue(deque, 2);
    CircularDeque_back_enqueue(deque, 3);
    CircularDeque_back_enqueue(deque, 4);
    CircularDeque_back_enqueue(deque, 5);
    CircularDeque_display(deque);

    CircularDeque_back_enqueue(deque, 6);
    CircularDeque_display(deque);

    CircularDequeEleType res;

    CircularDeque_back_dequeue(deque, &res);
    CircularDeque_display(deque);

    CircularDeque_back_dequeue(deque, &res);
    CircularDeque_back_dequeue(deque, &res);
    CircularDeque_back_dequeue(deque, &res);
    CircularDeque_back_dequeue(deque, &res);
    CircularDeque_display(deque);

    CircularDeque_front_dequeue(deque, &res);
    CircularDeque_display(deque);

    CircularDeque_back_enqueue(deque, 6);
    CircularDeque_display(deque);

    CircularDeque_front_enqueue(deque, 6);
    CircularDeque_display(deque);

    CircularDeque_clean(&deque);
    CircularDeque_display(deque);
    
    return 0;
}