#ifndef STACK_H_
#define STACK_H_

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
    "StackAccessException: Check whether parameter `Stack*` is valid ?\n"

#define STACK_PUSH_ERROR \
    "StackPushException: The Stack structure is full\n"

#define STACK_POP_ERROR \
    "StackPopException: The Stack structure is empty or buffer is NULL\n"


typedef enum StackInitModeEnum {
    STACK_INIT_DISABLE,
    STACK_INIT_ENABLE
} StackInitModeEnum;


typedef int StackEleType;


typedef struct Stack {
    StackEleType* data;
    StackEleType init_data;
    size_t length;
    size_t size;
    int is_init;
} Stack;


Stack* Stack_create(size_t size, StackInitModeEnum is_init, StackEleType* init);

int Stack_is_full(Stack* stack);

int Stack_is_empty(Stack* stack);

int Stack_push(Stack* stack, StackEleType ele);

int Stack_pop(Stack* stack, StackEleType* buf);

int Stack_clean(Stack** stack);

int Stack_display(Stack* stack);

#endif