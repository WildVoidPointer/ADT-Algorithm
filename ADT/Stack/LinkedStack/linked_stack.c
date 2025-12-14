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
    stack->head->next = stack->head->prev = NULL;
    stack->back = stack->head;
    return stack;
}


int LinkedStack_is_full(LinkedStack* stack) {
    return stack->length >= stack->size;
}


int LinkedStack_is_empty(LinkedStack* stack) {
    return stack->head == stack->back;
}


size_t LinkedStack_length(LinkedStack* stack) {
    return stack->length;
}


size_t LinkedStack_size(LinkedStack* stack) {
    return stack->size;
}


int LinkedStack_push(LinkedStack* stack, LinkedStackDataType ele) {
    if (stack == NULL) {
        fprintf(stderr, LINKED_STACK_ACCESS_EXCEPTION);
        return -1;
    }

    if (! LinkedStack_is_full(stack)) {
        LinkedStackNode* new = LinkedStackNode_create(&ele);
        if (new == NULL) {
            fprintf(stderr, LINKED_STACK_PUSH_ERROR);
            return -1;
        }
        new->prev = stack->back;
        stack->back->next = new;
        stack->back = stack->back->next;
        stack->length++;
        return 0;
    } else {
        fprintf(stderr, LINKED_STACK_PUSH_EXCEPTION);
        return -1;
    }
}


int LinkedStack_pop(
    LinkedStack* stack, LinkedStackDataType* popped
) {
    if (stack == NULL) {
        fprintf(stderr, LINKED_STACK_ACCESS_EXCEPTION);
        return -1;
    }

    if (popped == NULL || LinkedStack_is_empty(stack)) {
        fprintf(stderr, LINKED_STACK_POP_EXCEPTION);
        return -1;
    }

    LinkedStackNode* popped_node = stack->back;

    stack->back = stack->back->prev;

    *popped = popped_node->data;

    LinkedStackNode_destroy(&popped_node);

    stack->length--;

    return 0;
}


int LinkedStack_destroy(LinkedStack** stack) {
    if (stack == NULL || *stack == NULL) {
        fprintf(stderr, LINKED_STACK_ACCESS_EXCEPTION);
        return -1;
    }

    LinkedStackNode* to_del = NULL;

    while ((*stack)->back != NULL) {
        to_del = (*stack)->back;
        (*stack)->back = (*stack)->back->prev;
        LinkedStackNode_destroy(&to_del);
    }

    free(*stack);

    *stack = NULL;

    return 0;
}


int LinkedStack_display(LinkedStack* stack) {
    if (stack == NULL) {
        fprintf(stderr, LINKED_STACK_ACCESS_EXCEPTION);
        return -1;
    }

    LinkedStackNode* curr = stack->head->next;

    size_t visited_idx = 0;

    printf("LinkedStack: {  ");
    while (curr != NULL && visited_idx < stack->length) {
        printf("%d  ", curr->data);
        curr = curr->next;
        visited_idx++;
    }
    printf("}\n");

    return 0;
}


LinkedStackNode* LinkedStackNode_create(LinkedStackDataType* data) {
    if (data == NULL) {
        fprintf(stderr, LINKED_STACK_NODE_DATA_ACCESS_EXCEPTION);
        return NULL;
    }

    LinkedStackNode* node = (LinkedStackNode*) malloc (
        sizeof(LinkedStackNode)
    );

    if (node == NULL) {
        fprintf(stderr, LINKED_STACK_NODE_CREATE_ERROR);
        return NULL;
    }

    node->data = *data;
    node->next = node->prev = NULL;

    return node;
}


int LinkedStackNode_destroy(LinkedStackNode** node){
    if (node == NULL || *node == NULL) {
        fprintf(stderr, LINKED_STACK_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*node);
    *node = NULL;
    return 0;
}


int LinkedStackNode_display(LinkedStackNode* node){
    if (node != NULL) {
        printf("%d  ", node->data);
        return 0;
    } else {
        return -1;
    }
}
