#ifndef SEQUENTIAL_STACK_H
#define SEQUENTIAL_STACK_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define STACK_INIT_ERROR \
    "StackInitError: Failed to allocate memory for the `Stack`\n"

#define STACK_ELEMENTS_INIT_ERROR \
    "StackInitError: Failed to allocate memory for the `elements` of `Stack`\n"

#define STACK_ACCESS_ERROR \
    "StackAccessException: Check whether parameter `Stack*` is valid\n"

#define STACK_PUSH_ERROR \
    "StackPushException: The Stack structure is full\n"

#define STACK_POP_ERROR \
    "StackPopException: The Stack structure is empty or buffer is NULL\n"

#define STACK_INIT_ENABLE 1

#define STACK_INIT_DISABLE 0


typedef int StackEleType;


typedef struct Stack {
    StackEleType* data;
    StackEleType init;
    size_t length;
    size_t size;
    int is_init;
} Stack;


Stack* stack_create(size_t size, int is_init, StackEleType* init);

int stack_is_full(Stack* stack);

int stack_is_empty(Stack* stack);

int stack_push(Stack* stack, StackEleType ele);

int stack_pop(Stack* stack, StackEleType* buf);

int stack_clean(Stack** stack);

int stack_display(Stack* stack);

#endif