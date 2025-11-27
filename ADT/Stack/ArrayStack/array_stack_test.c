#include "array_stack.h"


int main(int argc, char const *argv[]) {

    ArrayStack* stack = ArrayStack_create(5);

    ArrayStack_display(stack);

    ArrayStack_push(stack, 23);
    ArrayStack_push(stack, 233);
    ArrayStack_push(stack, 2333);
    ArrayStack_push(stack, 23333);
    ArrayStack_push(stack, 233333);
    ArrayStack_display(stack);
    ArrayStack_push(stack, 2333333);
    ArrayStack_display(stack);

    ArrayStackDataType buf;

    ArrayStack_pop(stack, &buf);
    ArrayStack_pop(stack, &buf);
    ArrayStack_pop(stack, &buf);
    ArrayStack_display(stack);
    
    ArrayStack_pop(stack, &buf);
    ArrayStack_pop(stack, &buf);
    ArrayStack_pop(stack, &buf);
    ArrayStack_display(stack);

    ArrayStack_destory(&stack);
    ArrayStack_destory(&stack);
    
    return 0;
}