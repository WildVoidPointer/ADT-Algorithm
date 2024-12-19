#include<stdio.h>
#include<string.h>


#define MAX_LENGTH 1000

typedef struct Stack {
    int numbers[MAX_LENGTH];
    int index;
} Stack;


void init(Stack *stack) {
    for (int i = 0; i < MAX_LENGTH; i++) {
        stack->numbers[i] = 0;
    }
    stack->index = 0;
}


void push(Stack *stack, int num) {
    stack->numbers[stack->index] = num;
    stack->index++;
}


void pop(Stack *stack) {
    stack->index--;
    stack->numbers[stack->index] = 0;
}


int is_empty(Stack *stack) {
    return stack->index == 0;
}


void decimal_to_other(Stack *stack, int num, int base) {
    char *place_value_map = "0123456789abcdef";
    while (num > 0) {
        int rem = num % base;
        push(stack, place_value_map[rem]);
        num = num / base;
    }
}


int main(int argc, char const *argv[]) {

    Stack stack;
    init(&stack);
    int decimal_data = 233;
    decimal_to_other(&stack, decimal_data, 16);
    for (int i = stack.index -1; i >= 0; i--)
        printf("%c", stack.numbers[i]);
    puts("");
    return 0;
}
