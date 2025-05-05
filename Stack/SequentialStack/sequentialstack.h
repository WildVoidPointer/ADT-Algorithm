#ifndef SEQUENTIAL_STACK_H
#define SEQUENTIAL_STACK_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define SEQUENTIAL_STACK_CREATE_ERROR \
    "SequentialStackInitError: Failed to allocate memory for the `SequentialStack`\n"

#define SEQUENTIAL_STACK_ELEMENTS_INIT_ERROR \
    "SequentialStackInitError: Failed to allocate memory for the `elements` of `SequentialStack`\n"

#define SEQUENTIAL_STACK_ACCESS_ERROR \
    "SequentialStackAccessException: Check whether parameter `SequentialStack*` is valid\n"

#define SEQUENTIAL_STACK_PUSH_ERROR \
    "SequentialStackPushException: The SequentialStack structure is full\n"

#define SEQUENTIAL_STACK_POP_ERROR \
    "SequentialStackPopException: The SequentialStack structure is empty or buffer is NULL\n"

#define SEQUENTIAL_STACK_INIT_ENABLE 1

#define SEQUENTIAL_STACK_INIT_DISABLE 0



typedef int SequentialStackEleType;


typedef struct SequentialStack {
    SequentialStackEleType* data;
    SequentialStackEleType init;
    size_t length;
    size_t size;
    int is_init;
} SequentialStack;


SequentialStack* sequential_stack_create(size_t size, int is_init, SequentialStackEleType* init);

int sequential_stack_is_full(SequentialStack* stack);

int sequential_stack_is_empty(SequentialStack* stack);

int sequential_stack_push(SequentialStack* stack, SequentialStackEleType ele);

int sequential_stack_pop(SequentialStack* stack, SequentialStackEleType* buf);

int sequential_stack_clean(SequentialStack** stack);

int sequential_stack_display(SequentialStack* stack);

#endif