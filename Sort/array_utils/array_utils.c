#include "array_utils.h"

#include <stdio.h>


void integer_array_println(char* desp, int array[], int len) {
    fputs(desp, stdout);
    for (int i = 0; i < len; i++) {
        printf("%d  ", array[i]);
    }
    putc('\n', stdout);
}