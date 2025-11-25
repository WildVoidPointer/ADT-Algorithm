#include "array_stack.h"


ArrayStack* ArrayStack_create(size_t size) {

    ArrayStack* stack = (ArrayStack*) malloc (sizeof(ArrayStack));
    if (stack == NULL) {
        fprintf(stderr, ARRAY_STACK_INIT_ERROR);
        return NULL;
    }

    stack->data = (ArrayStackDataType*) malloc (
        size * sizeof(ArrayStackDataType)
    );
    if (stack->data == NULL) {
        fprintf(stderr, ARRAY_STACK_ELEMENTS_INIT_ERROR);
        free(stack);
        return NULL;
    }

    stack->size = size;
    stack->length = 0;

    return stack;
}


int ArrayStack_is_full(ArrayStack* stack) {
    return stack != NULL ? stack->length + 1 > stack->size : -1;
}


int ArrayStack_is_empty(ArrayStack* stack) {
    return stack != NULL ? stack->length == 0 : -1;
}


int ArrayStack_push(ArrayStack* stack, ArrayStackDataType ele) {
    if (stack == NULL) {
        fprintf(stderr, ARRAY_STACK_ACCESS_ERROR);
        return -1;
    }

    if (ArrayStack_is_full(stack)) {
        fprintf(stderr, ARRAY_STACK_PUSH_ERROR);
        return -1;
    }

    stack->data[stack->length] = ele;
    stack->length++;
    return 0;
}


int ArrayStack_pop(ArrayStack* stack, ArrayStackDataType* popped) {

    if (stack == NULL) {
        fprintf(stderr, ARRAY_STACK_ACCESS_ERROR);
        return -1;
    }

    if (ArrayStack_is_empty(stack) || popped == NULL) {
        fprintf(stderr, ARRAY_STACK_POP_ERROR);
        return -1;
    }

    *popped = stack->data[--(stack->length)];

    return 0;
}


int ArrayStack_clean(ArrayStack** stack) {
    if (stack == NULL || (*stack) == NULL) {
        fprintf(stderr, ARRAY_STACK_ACCESS_ERROR);
        return -1;
    }
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
    return 0;
}


int ArrayStack_display(ArrayStack* stack) {
    if (stack == NULL) {
        fprintf(stderr, ARRAY_STACK_ACCESS_ERROR);
        return -1;
    }

    printf("ArrayStack {  ");
    for (int i = 0; i < stack->length; i++) {
        printf("%d  ", stack->data[i]);
    }
    printf("}  length: %zu    size: %zu\n", stack->length, stack->size);
    return 0;
}
