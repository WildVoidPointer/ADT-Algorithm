#include "sequential_stack.h"


int main(int argc, char const *argv[]) {

    SequentialStackEleType init = -1;

    SequentialStack* stack = sequential_stack_create(
        5, SEQUENTIAL_STACK_INIT_ENABLE, &init);

    sequential_stack_display(stack);

    sequential_stack_push(stack, 23);
    sequential_stack_push(stack, 233);
    sequential_stack_push(stack, 2333);
    sequential_stack_push(stack, 23333);
    sequential_stack_push(stack, 233333);
    sequential_stack_display(stack);
    sequential_stack_push(stack, 2333333);
    sequential_stack_display(stack);

    SequentialStackEleType buf;

    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_display(stack);
    
    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_display(stack);

    sequential_stack_clean(&stack);
    sequential_stack_clean(&stack);
    
    return 0;
}