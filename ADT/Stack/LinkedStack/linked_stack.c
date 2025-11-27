#include "linked_stack.h"


LinkedStack* LinkedStack_create(size_t size) {
    LinkedStack* stack = (LinkedStack*) malloc (sizeof(LinkedStack));
    if (stack == NULL) {
        fprintf(stderr, LINKED_STACK_CREATE_ERROR);
        return NULL;
    }

    stack->head = (LinkedStackNode*) malloc (sizeof(LinkedStackNode));
    if (stack->head == NULL) {
        fprintf(stderr, LINKED_STACK_ACCESS_EXCEPTION);
        free(stack);
        return NULL;
    }

    stack->size = size;
    stack->length = 0;
    stack->back = stack->head;
    return stack;
}


int LinkedStack_is_full(LinkedStack* stack) {
    return stack->length >= stack->size;
}


int LinkedStack_is_empty(LinkedStack* stack) {
    return stack->head == stack->back;
}


int LinkedStack_push(LinkedStack* stack, LinkedStackDataType ele) {
    if (stack == NULL) {
        fprintf(stderr, LINKED_STACK_ACCESS_EXCEPTION);
        return -1;
    }

    if (!LinkedStack_is_full(stack)) {
        LinkedStackNode* new = LinkedStackNode_create(&ele);
        if (new == NULL) {
            fprintf(stderr, LINKED_STACK_PUSH_ERROR);
            return -1;
        }
        stack->back = stack->back->next;
        stack->back = new;
        return 0;
    } else {
        fprintf(stderr, LINKED_STACK_PUSH_EXCEPTION);
        return -1;
    }
}


int LinkedStack_pop(LinkedStack* stack, LinkedStackDataType* popped);

int LinkedStack_clear(LinkedStack* stack);

int LinkedStack_destroy(LinkedStack** stack);

int LinkedStack_display(LinkedStack* stack);

LinkedStackNode* LinkedStackNode_create(LinkedStackDataType* data);

int LinkedStackNode_destroy(LinkedStackNode** node);

int LinkedStackNode_display(LinkedStackNode* node);

