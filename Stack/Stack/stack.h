#ifndef SEQUENTIAL_STACK_H
#define SEQUENTIAL_STACK_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define STACK_INIT_ERROR \
    "StackInitError: Failed to allocate memory for the `SequentialStack`\n"

#define STACK_ELEMENTS_INIT_ERROR \
    "StackInitError: Failed to allocate memory for the `elements` of `SequentialStack`\n"

#define STACK_ACCESS_ERROR \
    "StackAccessException: Check whether parameter `SequentialStack*` is valid\n"

#define STACK_PUSH_ERROR \
    "StackPushException: The SequentialStack structure is full\n"

#define STACK_POP_ERROR \
    "SequentialStackPopException: The SequentialStack structure is empty or buffer is NULL\n"

#define STACK_INIT_ENABLE 1

#define STACK_INIT_DISABLE 0


typedef int SequentialStackEleType;


typedef struct SequentialStack {
    SequentialStackEleType* data;
    SequentialStackEleType init;
    size_t length;
    size_t size;
    int is_init;
} SequentialStack;


SequentialStack* stack_create(size_t size, int is_init, SequentialStackEleType* init);

int stack_is_full(SequentialStack* stack);

int stack_is_empty(SequentialStack* stack);

int stack_push(SequentialStack* stack, SequentialStackEleType ele);

int stack_pop(SequentialStack* stack, SequentialStackEleType* buf);

int stack_clean(SequentialStack** stack);

int stack_display(SequentialStack* stack);

#endif