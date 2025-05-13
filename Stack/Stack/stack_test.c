#include "stack.h"


int main(int argc, char const *argv[]) {

    SequentialStackEleType init = -1;

    SequentialStack* stack = stack_create(
        5, STACK_INIT_ENABLE, &init);

    stack_display(stack);

    stack_push(stack, 23);
    stack_push(stack, 233);
    stack_push(stack, 2333);
    stack_push(stack, 23333);
    stack_push(stack, 233333);
    stack_display(stack);
    stack_push(stack, 2333333);
    stack_display(stack);

    SequentialStackEleType buf;

    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_display(stack);
    
    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_display(stack);

    stack_clean(&stack);
    stack_clean(&stack);
    
    return 0;
}