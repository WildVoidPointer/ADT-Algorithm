#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static struct OpsPrecMap {

    struct {
        char op;
        int precedence;
    } units[5];

    int len;

} DefaultOpsPrecMap = {

    .units = { 
        { .op = '+', .precedence = 2 },
        { .op = '-', .precedence = 2 },
        { .op = '*', .precedence = 3 },
        { .op = '/', .precedence = 3 },
        { .op = '(', .precedence = 1 },
    },
    .len = 5
};



static int prec_map_get_precedence(
    struct OpsPrecMap *prec, char op
) {
    for (int i = 0; i < prec->len; i++) {
        if (prec->units[i].op == op) {
            return prec->units[i].precedence;
        }
    }
    return -1;
}


static int prec_map_prec_cmp_gt(
    struct OpsPrecMap *prec, 
    char c1, char c2
) {
    int prec_c1 = 0;
    int prec_c2 = 0;

    for (int i = 0; i < prec->len; i++) {
        if (c1 == prec->units[i].op) {
            prec_c1 = prec->units[i].precedence;
        }

        if (c2 == prec->units[i].op) {
            prec_c2 = prec->units[i].precedence;
        }
    }

    return prec_c1 >= prec_c2;
}


struct Stack {
    char* chars;
    int len;
    int size;
};


static struct Stack* stack_create(int size) {

    if (size <= 0) {
        return NULL;
    }

    struct Stack* st = malloc (sizeof(struct Stack));
    if (st == NULL) {
        return NULL;
    }

    st->chars = malloc (sizeof(char) * size);
    if (st->chars == NULL) {
        free(st);
        return NULL;
    }

    st->size = size;

    st->len = 0;
}


static void stack_push(struct Stack *stack, char op) {
    if (stack->len >= stack->size) {
        return;
    }
    stack->chars[stack->len++] = op;
}


static char stack_pop(struct Stack* stack) {
    if (stack->len <= 0) {
        return '\0';
    }
    char popped = stack->chars[--(stack->len)];

    return popped;
}


static char stack_peek(struct Stack* stack) {
    return stack->chars[stack->len - 1];
}


static int stack_is_empty(struct Stack* stack) {
    return stack->len <= 0;
}


static void stack_println(struct Stack* stack) {
    for (int i = 0; i < stack->len; i++) {
        printf("%c  ", stack->chars[i]);
    }

    printf("\n");
}


static int char_is_letter(char c) {
    if (
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')
    ) {
        return 1;
    } else {
        return 0;
    }
}


static int char_is_op(
    struct OpsPrecMap* prec_map, char c
) {
    
    for (int i = 0; i < prec_map->len; i++) {
        if (c == prec_map->units[i].op) {
            return 1;
        }
    }

    return 0;
}


static void println_postfix_of_infix(
    struct OpsPrecMap* prec_map,
    char* infix,
    int infix_len
) {
    struct Stack* st = stack_create(30);

    if (st == NULL) {
        return;
    }

    struct Stack* postfix = stack_create(infix_len);
    if (postfix == NULL) {
        return;
    }

    for (int i = 0; i < infix_len; i++) {

        if (char_is_letter(infix[i])) {

            stack_push(postfix, infix[i]);

        } else if (infix[i] == ')') {
            // 需要单独处理括号 此处仅有 "(" 与 ")
            while (stack_peek(st) != '(') {
                stack_push(postfix, stack_pop(st));
            }

            stack_pop(st);

        } else if (char_is_op(prec_map, infix[i])) {
            while (
                ! stack_is_empty(st) 
                && prec_map_prec_cmp_gt(
                    prec_map,
                    stack_peek(st),
                    infix[i]
                )
                && stack_peek(st) != '('
            ) {
                stack_push(postfix, stack_pop(st));
            }

            stack_push(st, infix[i]);
        }
    }

    while (! stack_is_empty(st)) {
        stack_push(postfix, stack_pop(st));
    }

    stack_println(postfix);
}


int main(int argc, char const *argv[]) {
    char* infix = "(A+B)*C";    // A B + C *

    int infix_len = strlen(infix);

    println_postfix_of_infix(
        &DefaultOpsPrecMap,
        infix,
        infix_len
    );
}
