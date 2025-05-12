#include "sequential_deque.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    SequentialDeque* deque = deque_create(5, DEQUE_INIT_DISABLE, NULL);

    deque_back_enqueue(deque, 1);
    deque_back_enqueue(deque, 2);
    deque_back_enqueue(deque, 3);
    deque_back_enqueue(deque, 4);
    deque_back_enqueue(deque, 5);
    deque_display(deque);

    deque_back_enqueue(deque, 6);
    deque_display(deque);

    SequentialDequeEleType res;

    deque_back_dequeue(deque, &res);
    deque_display(deque);

    deque_back_dequeue(deque, &res);
    deque_back_dequeue(deque, &res);
    deque_back_dequeue(deque, &res);
    deque_back_dequeue(deque, &res);
    deque_display(deque);

    deque_front_dequeue(deque, &res);
    deque_display(deque);

    deque_back_enqueue(deque, 6);
    deque_display(deque);

    deque_front_enqueue(deque, 6);
    deque_display(deque);

    deque_clean(&deque);
    deque_display(deque);
    
    return 0;
}