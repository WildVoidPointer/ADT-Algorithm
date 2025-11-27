#ifndef ARRAY_STACK_H_
#define ARRAY_STACK_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define ARRAY_STACK_INIT_ERROR \
    "ArrayStackInitError: " \
    "Failed to allocate memory for the `ArrayStack`\n"


#define ARRAY_STACK_ELEMENTS_INIT_ERROR \
    "ArrayStackInitError: " \
    "Failed to allocate memory for the `elements` of `ArrayStack`\n"


#define ARRAY_STACK_ACCESS_ERROR \
    "ArrayStackAccessException: " \
    "Check whether parameter `ArrayStack*` is valid ?\n"


#define ARRAY_STACK_PUSH_ERROR \
    "ArrayStackPushException: The ArrayStack is full\n"


#define ARRAY_STACK_POP_ERROR \
    "ArrayStackPopException: " \
    "The ArrayStack is empty or buffer is NULL\n"


typedef int ArrayStackDataType;


typedef struct ArrayStack {
    ArrayStackDataType* data;
    size_t length;
    size_t size;
} ArrayStack;


ArrayStack* ArrayStack_create(size_t size);

int ArrayStack_is_full(ArrayStack* stack);

int ArrayStack_is_empty(ArrayStack* stack);

int ArrayStack_push(ArrayStack* stack, ArrayStackDataType ele);

int ArrayStack_pop(ArrayStack* stack, ArrayStackDataType* buf);

int ArrayStack_destory(ArrayStack** stack);

int ArrayStack_display(ArrayStack* stack);

#endif