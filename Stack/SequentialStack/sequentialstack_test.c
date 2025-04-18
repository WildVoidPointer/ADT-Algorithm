#include "sequentialstack.h"

int main(int argc, char const *argv[])
{
    SequentialStack* stack = sequential_stack_create(5, 1, -1);
    sequential_stack_display(stack);

    sequential_stack_push(stack, 23);
    sequential_stack_push(stack, 233);
    sequential_stack_push(stack, 2333);
    sequential_stack_push(stack, 23333);
    sequential_stack_push(stack, 233333);
    sequential_stack_display(stack);
    sequential_stack_push(stack, 2333333);

    SequentialStackEleType buf;

    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_display(stack);
    
    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);
    sequential_stack_pop(stack, &buf);

    sequential_stack_clean(&stack);
    sequential_stack_clean(&stack);
    
    return 0;
}