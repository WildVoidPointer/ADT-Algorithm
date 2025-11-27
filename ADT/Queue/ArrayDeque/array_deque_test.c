#include "array_deque.h"
#include <stdio.h>


int main(int argc, char const *argv[]) {
    ArrayDeque* deque = ArrayDeque_create(5);

    ArrayDeque_back_enqueue(deque, 1);
    ArrayDeque_back_enqueue(deque, 2);
    ArrayDeque_back_enqueue(deque, 3);
    ArrayDeque_back_enqueue(deque, 4);
    ArrayDeque_back_enqueue(deque, 5);
    ArrayDeque_display(deque);

    ArrayDeque_back_enqueue(deque, 6);
    ArrayDeque_display(deque);

    ArrayDequeDataType res;

    ArrayDeque_back_dequeue(deque, &res);
    ArrayDeque_display(deque);

    ArrayDeque_back_dequeue(deque, &res);
    ArrayDeque_back_dequeue(deque, &res);
    ArrayDeque_back_dequeue(deque, &res);
    ArrayDeque_back_dequeue(deque, &res);
    ArrayDeque_display(deque);

    ArrayDeque_front_dequeue(deque, &res);
    ArrayDeque_display(deque);

    ArrayDeque_back_enqueue(deque, 6);
    ArrayDeque_display(deque);

    ArrayDeque_front_enqueue(deque, 6);
    ArrayDeque_display(deque);

    ArrayDeque_destroy(&deque);
    ArrayDeque_display(deque);
    
    return 0;
}