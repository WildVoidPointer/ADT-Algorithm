#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    return st;
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


static int bracket_is_matched(struct Stack* st, char op) {
    while (! stack_is_empty(st) && stack_peek(st) != op) {
        stack_pop(st);
    }

    if (stack_peek(st) == op) {
        stack_pop(st);
        return 1;
    } else {
        return 0;
    }
}


static int bracket_matching(char* s, int s_len) {
    if (s_len <= 0) {
        return 1;
    }
    
    struct Stack* st = stack_create(s_len);

    for (int i = 0; i < s_len; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack_push(st, s[i]);
        } else if (s[i] == ')') {
            if (! bracket_is_matched(st, '(')) {
                return 0;
            }
        } else if (s[i] == ']') {
            if (! bracket_is_matched(st, '[')) {
                return 0;
            }
        } else if (s[i] == '}') {
            if (! bracket_is_matched(st, '{')) {
                return 0;
            }
        }
    }

    if (stack_is_empty(st)) {
        return 1;
    } else {
        return 0;
    }
}


int main() {
    // 测试用例
    char* test_cases[] = {
        "()",           // 匹配
        "()[]{}",       // 匹配
        "({[]})",       // 匹配
        "(]",           // 不匹配
        "([)]",         // 不匹配
        "((()))",       // 匹配
        "((())",        // 不匹配
        "",             // 空字符串，匹配
        "{[()]}",       // 匹配
        "{{{{",         // 不匹配
        "}}}}",         // 不匹配
        "(a+b)*[c-d]",  // 匹配（包含其他字符）
        "([{)]}",       // 不匹配
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        char* str = test_cases[i];
        int len = strlen(str);
        int result = bracket_matching(str, len);
        
        printf("测试 %2d: \"%s\" -> %s\n", 
               i + 1, 
               str, 
               result ? "匹配 ✓" : "不匹配 ✗");
    }
    
    return 0;
}
