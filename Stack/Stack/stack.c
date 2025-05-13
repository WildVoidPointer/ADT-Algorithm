#include "stack.h"


Stack* 
stack_create(size_t size, int is_init, StackEleType* init) {

    Stack* stack = (Stack*) malloc (sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, STACK_INIT_ERROR);
        return NULL;
    }
    stack->data = (StackEleType*) malloc (size * sizeof(StackEleType));
    if (stack->data == NULL) {
        fprintf(stderr, STACK_ELEMENTS_INIT_ERROR);
        free(stack);
        return NULL;
    }

    stack->size = size;
    stack->length = 0;

    if (is_init) {
        stack->init = *init;
        stack->is_init = 1;
        for (int i = 0; i < size; i++) {
            stack->data[i] = *init;
        }
    } else {
        stack->is_init = 0;
    }

    return stack;
}


int stack_is_full(Stack* stack) {
    return stack != NULL ? stack->length + 1 > stack->size : -1;
}


int stack_is_empty(Stack* stack) {
    return stack != NULL ? stack->length == 0 : -1;
}


int stack_push(Stack* stack, StackEleType ele) {
    if (stack == NULL) {
        fprintf(stderr, STACK_ACCESS_ERROR);
        return -1;
    }

    if (stack_is_full(stack)) {
        fprintf(stderr, STACK_PUSH_ERROR);
        return -1;
    }

    stack->data[stack->length] = ele;
    stack->length++;
    return 0;
}


int stack_pop(Stack* stack, StackEleType* buf) {
    if (stack == NULL) {
        fprintf(stderr, STACK_ACCESS_ERROR);
        return -1;
    }

    if (stack_is_empty(stack) || buf == NULL) {
        fprintf(stderr, STACK_POP_ERROR);
        return -1;
    }

    *buf = stack->data[--stack->length];

    if (stack->is_init) {
        stack->data[stack->length] = stack->init;
    }
    return 0;
}


int stack_clean(Stack** stack) {
    if (stack == NULL || (*stack) == NULL) {
        fprintf(stderr, STACK_ACCESS_ERROR);
        return -1;
    }
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
    return 0;
}


int stack_display(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, STACK_ACCESS_ERROR);
        return -1;
    }

    printf("SequentialStack {  ");
    for (int i = 0; i < stack->length; i++) {
        printf("%d  ", stack->data[i]);
    }
    printf("}  length: %zu    size: %zu\n", stack->length, stack->size);
    return 0;
}
