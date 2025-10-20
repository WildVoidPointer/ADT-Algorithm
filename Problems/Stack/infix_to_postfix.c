#include<stdio.h>
#include<string.h>


#define MAX_LENGTH 1000


typedef struct PrecMap {
    char symbol;
    int precedence;
} PrecMap;


int get_precedence(PrecMap *prec, int len, char op) {
    for (int i = 0; i < len; i++) {
        if (prec[i].symbol == op) {
            return prec[i].precedence;
        }
    }
    return -1;
}


typedef struct Stack {
    char characters[MAX_LENGTH];
    int index;
} Stack;


void init(Stack *stack) {
    for (int i = 0; i < MAX_LENGTH; i++) {
        stack->characters[i] = '\0';
    }
    stack->index = 0;
}


void push(Stack *stack, char num) {
    stack->characters[stack->index] = num;
    stack->index++;
}


char pop(Stack *stack) {
    stack->index--;
    char _pop_ele = stack->characters[stack->index];
    stack->characters[stack->index] = '\0';
    return _pop_ele;
}


char peek(Stack *stack) {
    return stack->characters[stack-> index - 1];
}


int is_empty(Stack *stack) {
    return stack->index == 0;
}


int main(int argc, char const *argv[]) {

    char *infix = "(A+B)*C";
    char *allow_chars = "ABCDEFGHIJKMNOPQRSTUVWXYZ";

    PrecMap prec[] = {
        {'+', 2},
        {'-', 2},
        {'*', 3},
        {'/', 3},
        {'(', 1}, 
    };
    const int prec_map_len = 5;

    Stack operators;
    init(&operators);

    Stack postfix;
    init(&postfix);

    int infix_len = strlen(infix);

    for (int i = 0; i < infix_len; i++) {

        char _infix_iter = infix[i];

        if (_infix_iter >= 'A' && _infix_iter <= 'Z' 
            || _infix_iter >= '0' && _infix_iter <= '9')

            push(&postfix, _infix_iter);

        else if (_infix_iter == '(')
            push(&operators, _infix_iter);

        else if (_infix_iter == ')') {
            char _top_op = pop(&operators);

            while (_top_op != '(') {
                push(&postfix, _top_op);
                _top_op = pop(&operators);
            }
        }

        else {
            while (!is_empty(&operators) && 
                (get_precedence(prec, prec_map_len, peek(&operators)) >= 
                    get_precedence(prec, prec_map_len, _infix_iter))) {
                push(&postfix, pop(&operators));
            }
            
            push(&operators, _infix_iter);
        }

    }

    while (! is_empty(&operators))
        push(&postfix, pop(&operators));

    if (! is_empty(&postfix)) {
        int _postfix_len = postfix.index;
        for (int i = 0; i < _postfix_len; i++) 
            printf("%c", postfix.characters[i]);
        puts("");
    }
    return 0;
}
