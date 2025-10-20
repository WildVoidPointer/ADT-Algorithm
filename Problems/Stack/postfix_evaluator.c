#include<stdio.h>
#include<string.h>


#define MAX_LENGTH 1000
typedef double EleType;


typedef struct Stack {
    EleType numbers[MAX_LENGTH];
    int index;
} Stack;


void init(Stack *stack) {
    for (int i = 0; i < MAX_LENGTH; i++) {
        stack->numbers[i] = 0;
    }
    stack->index = 0;
}


void push(Stack *stack, EleType num) {
    stack->numbers[stack->index] = num;
    stack->index++;
}


double pop(Stack *stack) {
    stack->index--;
    double _pop_ele = stack->numbers[stack->index];
    stack->numbers[stack->index] = 0;
    return _pop_ele;
}


int peek(Stack *stack) {
    return stack->numbers[stack-> index - 1];
}


int is_empty(Stack *stack) {
    return stack->index == 0;
}


int main(int argc, char const *argv[]) {
    
    char *postfix = "3 4 + 5 *";
    char *allow_opts = "+-*/";

    int len_of_postfix = strlen(postfix);
    int len_of_allow_ops = strlen(allow_opts);

    Stack data;
    init(&data);

    for (int i = 0; i < len_of_postfix; i++) {
        char _current_iter = postfix[i];
        if (_current_iter >= '0' && _current_iter <= '9') {
            push(&data, (EleType)(_current_iter - '0'));
        }

        int _allow_op_flag = 0;
        for (int _ = 0; _ < len_of_allow_ops; _++) {
            if (_current_iter == allow_opts[_]) {
                _allow_op_flag = 1;
                break;
            }
        }

        if (_allow_op_flag && data.index >= 2) {
            EleType right_operand = pop(&data);
            EleType left_operand = pop(&data);
            EleType result = 0;

            switch (_current_iter) {
            case '+':
                result = left_operand + right_operand;
                break;
            case '-':
                result = left_operand - right_operand;
                break;
            case '*':
                result = left_operand * right_operand;
                break;
            case '/':
                result = left_operand / right_operand;
                break;
            }

            push(&data, result);
        }

    }
    
    printf("Result: %.2g\n", data.numbers[data.index - 1]);
    return 0;
}
