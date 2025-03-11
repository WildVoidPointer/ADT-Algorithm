#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif

typedef int StackEleType;


typedef struct Stack {
    StackEleType* data;
    StackEleType init_data;
    size_t length;
    size_t size;
    int init_state;
} Stack;


Stack* stack_create(size_t size, int is_init, StackEleType init_data) {
    Stack* stack = (Stack*) malloc (sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "StackInitError: Failed to allocate memory for the `Stack`\n");
        return NULL;
    }
    stack->data = (StackEleType*) malloc (size * sizeof(StackEleType));
    if (stack->data == NULL) {
        fprintf(stderr, "StackInitError: Failed to allocate memory for the `elements` of `Deque`\n");
        free(stack);
        return NULL;
    }

    stack->size = size;
    stack->length = 0;

    if (is_init) {
        stack->init_data = init_data;
        stack->init_state = 1;
        for (int i = 0; i < size; i++) {
            stack->data[i] = init_data;
        }
    } else {
        stack->init_state = 0;
    }

    return stack;
}


int stack_is_full(Stack* stack) {
    return stack->length >= stack->size;
}


int stack_is_empty(Stack* stack) {
    return stack->length == 0;
}


int stack_push(Stack* stack, StackEleType ele) {
    if (stack == NULL) {
        fprintf(stderr, "StackAccessException: Check whether parameter `Stack*` is valid\n");
        return -1;
    }

    if (stack_is_full(stack)) {
        fprintf(stderr, "StackPushException: The Stack structure is full\n");
        return -1;
    }

    stack->data[stack->length] = ele;
    stack->length++;
    return 0;
}


int stack_pop(Stack *stack, StackEleType* buf) {
    if (stack == NULL || buf == NULL) {
        fprintf(stderr, "StackAccessException: Check whether parameter `Stack*` or `buf*` is valid\n");
        return -1;
    }

    if (stack_is_empty(stack)) {
        fprintf(stderr, "StackPopException: The Stack structure is empty\n");
        return -1;
    }

    *buf = stack->data[--stack->length];

    if (stack->init_state) {
        stack->data[stack->length] = stack->init_data;
    }
    return 0;
}


int stack_clean(Stack** stack) {
    if (stack == NULL || (*stack) == NULL) {
        fprintf(stderr, "StackAccessException: Check whether parameter `Stack**` is valid\n");
        return -1;
    }
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
    return 0;
}


int stack_display(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "StackAccessException: Check whether parameter `Stack*` is valid\n");
        return -1;
    }

    printf("Satck {  ");
    for (int i = 0; i < stack->length; i++) {
        printf("%d  ", stack->data[i]);
    }
    printf("}  length: %zu    size: %zu\n", stack->length, stack->size);
    return 0;
}





int main(int argc, char const *argv[])
{
    Stack* stack = stack_create(5, 1, -1);
    stack_display(stack);

    stack_push(stack, 23);
    stack_push(stack, 233);
    stack_push(stack, 2333);
    stack_push(stack, 23333);
    stack_push(stack, 233333);
    stack_display(stack);
    stack_push(stack, 2333333);

    StackEleType buf;

    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_display(stack);
    
    stack_pop(stack, &buf);
    stack_pop(stack, &buf);
    stack_pop(stack, &buf);

    stack_clean(&stack);
    stack_clean(&stack);
    
    return 0;
}
