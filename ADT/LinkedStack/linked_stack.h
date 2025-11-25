#ifndef LINKED_STACK_H_
#define LINKED_LINKED_STACK_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define LINKED_STACK_INIT_ERROR \
    "LinkedStackInitError: " \
    "Failed to allocate memory for the `LinkedStack`\n"


#define LINKED_STACK_ELEMENTS_INIT_ERROR \
    "LinkedStackInitError: " \
    "Failed to allocate memory for the `elements` of `LinkedStack`\n"


#define LINKED_STACK_ACCESS_ERROR \
    "LinkedStackAccessException: Check whether parameter `LinkedStack*` is valid ?\n"


#define LINKED_STACK_PUSH_ERROR \
    "LinkedStackPushException: The LinkedStack structure is full\n"


#define LINKED_STACK_POP_ERROR \
    "LinkedStackPopException: " \
    "The LinkedStack structure is empty or buffer is NULL\n"


typedef int LinkedStackDataType;


typedef struct LinkedStackNode {
    LinkedStackDataType data;
    struct LinkedStackNode* next;
} LinkedStackNode;


typedef struct LinkedStack {
    LinkedStackDataType* head;
    size_t length;
    size_t size;
} LinkedStack;


LinkedStack* LinkedStack_create(size_t size);

int LinkedStack_is_full(LinkedStack* stack);

int LinkedStack_is_empty(LinkedStack* stack);

int LinkedStack_push(LinkedStack* stack, LinkedStackDataType ele);

int LinkedStack_pop(LinkedStack* stack, LinkedStackDataType* buf);

int LinkedStack_clear(LinkedStack* stack);

int LinkedStack_clean(LinkedStack** stack);

int LinkedStack_display(LinkedStack* stack);

LinkedStackNode* LinkedStackNode_create();

int LinkedStackNode_clean(LinkedStackNode** node);

int LinkedStackNode_display(LinkedStackNode* node);

#endif
