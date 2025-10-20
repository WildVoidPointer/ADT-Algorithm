#include "stack.h"


int main(int argc, char const *argv[]) {

    StackEleType init = -1;

    Stack* stack = Stack_create(
        5, STACK_INIT_ENABLE, &init);

    Stack_display(stack);

    Stack_push(stack, 23);
    Stack_push(stack, 233);
    Stack_push(stack, 2333);
    Stack_push(stack, 23333);
    Stack_push(stack, 233333);
    Stack_display(stack);
    Stack_push(stack, 2333333);
    Stack_display(stack);

    StackEleType buf;

    Stack_pop(stack, &buf);
    Stack_pop(stack, &buf);
    Stack_pop(stack, &buf);
    Stack_display(stack);
    
    Stack_pop(stack, &buf);
    Stack_pop(stack, &buf);
    Stack_pop(stack, &buf);
    Stack_display(stack);

    Stack_clean(&stack);
    Stack_clean(&stack);
    
    return 0;
}