#ifndef SEQUENTIAL_STACK_H
#define SEQUENTIAL_STACK_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define SEQUENTIAL_STACK_INIT_ERROR_MEMORY "SequentialStackInitError: Failed to allocate memory for the `SequentialStack`\n"
#define SEQUENTIAL_STACK_INIT_ERROR_ELEMENTS "SequentialStackInitError: Failed to allocate memory for the `elements` of `SequentialStack`\n"
#define SEQUENTIAL_STACK_ACCESS_ERROR "SequentialStackAccessException: Check whether parameter `SequentialStack*` is valid\n"
#define SEQUENTIAL_STACK_ACCESS_ERROR_DOUBLE_PTR "SequentialStackAccessException: Check whether parameter `SequentialStack**` is valid\n"
#define SEQUENTIAL_STACK_ACCESS_ERROR_BUF "SequentialStackAccessException: Check whether parameter `SequentialStack*` or `buf*` is valid\n"
#define SEQUENTIAL_STACK_PUSH_ERROR "SequentialStackPushException: The SequentialStack structure is full\n"
#define SEQUENTIAL_STACK_POP_ERROR "SequentialStackPopException: The SequentialStack structure is empty\n"

typedef int SequentialStackEleType;

typedef struct SequentialStack {
    SequentialStackEleType* data;
    SequentialStackEleType init;
    size_t length;
    size_t size;
    int init_state;
} SequentialStack;

SequentialStack* sequential_stack_create(size_t size, int is_init, SequentialStackEleType init);
int sequential_stack_is_full(SequentialStack* stack);
int sequential_stack_is_empty(SequentialStack* stack);
int sequential_stack_push(SequentialStack* stack, SequentialStackEleType ele);
int sequential_stack_pop(SequentialStack* stack, SequentialStackEleType* buf);
int sequential_stack_clean(SequentialStack** stack);
int sequential_stack_display(SequentialStack* stack);

#endif