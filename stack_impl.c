#include <stdio.h>
#include <stdbool.h>


#define MAX_LENGTH 233
#define INTI_DATA 0

typedef int EleType;


struct Stack {
    EleType data[MAX_LENGTH];
    int index;
};


// Use a struct pointer to pass the stack structure.
void initialize(struct Stack *stack) {
    for (int i = 0; i < MAX_LENGTH; i++) {
        stack->data[i] = INTI_DATA;
    }
    stack->index = 0;
}


bool push(struct Stack *stack, int ele) {
    if (stack->index == MAX_LENGTH)
        return false;
    stack->data[stack->index] = ele;
    stack->index++;
    return true;
}


EleType pop(struct Stack *stack) {
    if (stack->index <= 0)
        return INTI_DATA;
        
    stack->index--;
    int _pop_ele = stack->data[stack->index];
    stack->data[stack->index] = 0;
    return _pop_ele;
}


bool is_empty(struct Stack *stack) {
    return stack->index <= 0;
}


int main() {
    struct Stack stack;
    
    initialize(&stack);
    push(&stack, 233);
    push(&stack, 2333);

    printf("%d\n", pop(&stack));
    printf("%d\n", stack.data[0]); 
    printf("%d\n", stack.index);

    return 0;
}
