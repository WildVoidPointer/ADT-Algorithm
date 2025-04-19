#include "sequentialstack.h"


SequentialStack* 
sequential_stack_create(size_t size, int is_init, SequentialStackEleType* init) {

    SequentialStack* stack = (SequentialStack*) malloc (sizeof(SequentialStack));
    if (stack == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_CREATE_ERROR);
        return NULL;
    }
    stack->data = (SequentialStackEleType*) malloc (size * sizeof(SequentialStackEleType));
    if (stack->data == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_ELEMENTS_INIT_ERROR);
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


int sequential_stack_is_full(SequentialStack* stack) {
    return stack != NULL ? stack->length + 1 > stack->size : -1;
}


int sequential_stack_is_empty(SequentialStack* stack) {
    return stack != NULL ? stack->length == 0 : -1;
}


int sequential_stack_push(SequentialStack* stack, SequentialStackEleType ele) {
    if (stack == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_ACCESS_ERROR);
        return -1;
    }

    if (sequential_stack_is_full(stack)) {
        fprintf(stderr, SEQUENTIAL_STACK_PUSH_ERROR);
        return -1;
    }

    stack->data[stack->length] = ele;
    stack->length++;
    return 0;
}


int sequential_stack_pop(SequentialStack* stack, SequentialStackEleType* buf) {
    if (stack == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_ACCESS_ERROR);
        return -1;
    }

    if (sequential_stack_is_empty(stack) || buf == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_POP_ERROR);
        return -1;
    }

    *buf = stack->data[--stack->length];

    if (stack->is_init) {
        stack->data[stack->length] = stack->init;
    }
    return 0;
}


int sequential_stack_clean(SequentialStack** stack) {
    if (stack == NULL || (*stack) == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_ACCESS_ERROR);
        return -1;
    }
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
    return 0;
}


int sequential_stack_display(SequentialStack* stack) {
    if (stack == NULL) {
        fprintf(stderr, SEQUENTIAL_STACK_ACCESS_ERROR);
        return -1;
    }

    printf("SequentialStack {  ");
    for (int i = 0; i < stack->length; i++) {
        printf("%d  ", stack->data[i]);
    }
    printf("}  length: %zu    size: %zu\n", stack->length, stack->size);
    return 0;
}
